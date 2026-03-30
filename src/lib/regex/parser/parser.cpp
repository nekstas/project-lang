#include "parser.h"

#include "../../utils/magic_templates.hpp"
#include "../../utils/utils.h"
#include "../ast/all.h"

#define U8(expr) static_cast<uint8_t>(expr)

namespace lib::regex {

namespace {

constexpr std::string_view kPossibleRepeatChars = "*+?";

template <typename T>
std::unique_ptr<ast::Node> MakeOptimalReturn(std::vector<std::unique_ptr<ast::Node>> nodes) {
    if (nodes.empty()) {
        return nullptr;
    } else if (nodes.size() == 1) {
        return std::move(nodes[0]);
    }
    return std::make_unique<T>(std::move(nodes));
}

enum class CharSetPrevType { NONE, CHAR, CHAR_CLASS };

}  // namespace

std::unique_ptr<ast::Node> Parser::Parse(const std::string& code) {
    SetCodeAndReset(code);
    return Parse();
}

std::unique_ptr<ast::Node> Parser::Parse() {
    auto result = ParseSequence();
    THROW_REGEX_PARSER_ERROR_IF(!IsEof(), "Expected eof.");
    return std::move(result);
}

std::unique_ptr<ast::Node> Parser::ParseSequence() {
    std::vector<std::unique_ptr<ast::Node>> nodes;
    while (!IsEof() && !::utils::IsIn(Peek(), "|)")) {
        auto node = ParseRepeat();
        THROW_REGEX_PARSER_ERROR_IF(!node, "Got empty subsequence while parsing sequence.");
        nodes.emplace_back(std::move(node));
    }

    return MakeOptimalReturn<ast::SequenceNode>(std::move(nodes));
}

std::unique_ptr<ast::Node> Parser::ParseRepeat() {
    auto result = ParseChoice();

    if (::utils::IsIn(Peek(), kPossibleRepeatChars)) {
        THROW_REGEX_PARSER_ERROR_IF(!result, "Can't repeat empty sequence.");
        THROW_REGEX_PARSER_ERROR_IF(
            ast::CastNode<ast::RepeatNode>(result.get()), "Repeat can't be inside another repeat.");

        const auto repeat_type = ast::RepeatCharToType(Consume());
        result = std::make_unique<ast::RepeatNode>(std::move(result), repeat_type);
    }

    THROW_REGEX_PARSER_ERROR_IF(
        ::utils::IsIn(Peek(), kPossibleRepeatChars), "Multiple repeat modifiers are unsupported.");

    return result;
}

std::unique_ptr<ast::Node> Parser::ParseChoice() {
    if (Peek() != '(') {
        return ParseCharSet();
    }

    Advance();
    std::vector<std::unique_ptr<ast::Node>> nodes;
    do {
        auto node = ParseSequence();
        THROW_REGEX_PARSER_ERROR_IF(!node, "Got empty subsequence while parsing choice.");
        nodes.emplace_back(std::move(node));
    } while (AdvanceIf('|'));
    Match(')');

    return MakeOptimalReturn<ast::ChoiceNode>(std::move(nodes));
}

std::unique_ptr<ast::Node> Parser::ParseCharSet() {
    if (Peek() != '[') {
        return ParseChar();
    }

    Advance();
    bool negated = AdvanceIf('^');
    ast::CharClassNode::DetailedMask mask;

    uint8_t prev_char;
    auto prev_type = CharSetPrevType::NONE;
    bool mask_was_extended = false;

    while (!AdvanceIf(']')) {
        bool is_range = AdvanceIf('-');

        auto process_alone_char = [&](uint8_t ch) {
            mask.ExtendFrom(ch);
            prev_type = CharSetPrevType::CHAR;
            prev_char = ch;
            mask_was_extended = true;
        };

        auto process_char = [&](uint8_t ch) {
            switch (prev_type) {
                case CharSetPrevType::NONE:
                case CharSetPrevType::CHAR_CLASS:
                    process_alone_char(ch);
                    break;
                case CharSetPrevType::CHAR:
                    if (is_range) {
                        THROW_REGEX_PARSER_ERROR_IF(prev_char > ch, "Inverted range order.");
                        mask.ExtendFrom(ast::CharSetNode::Range{prev_char, ch});
                        prev_type = CharSetPrevType::NONE;
                        mask_was_extended = true;
                    } else {
                        process_alone_char(ch);
                    }
                    break;
                default:
                    UNREACHABLE;
            }
        };

        auto process_char_class = [&](const CharClassDesc& desc) {
            THROW_REGEX_PARSER_ERROR_IF(is_range && prev_type == CharSetPrevType::CHAR,
                "Can't create a range with char class.");
            auto another_mask = ast::CharClassNode::ConstructDetailedMask(desc.char_class);
            mask.ExtendFrom(desc.negated ? ~another_mask : another_mask);
            prev_type = CharSetPrevType::CHAR_CLASS;
            mask_was_extended = true;
        };

        if (is_range) {
            switch (prev_type) {
                case CharSetPrevType::NONE:
                    mask.ExtendFrom('-');
                    break;
                case CharSetPrevType::CHAR_CLASS:
                    THROW_REGEX_PARSER_ERROR_IF(
                        Peek() != ']', "Can't create a range with char class.");
                case CharSetPrevType::CHAR:
                    break;
                default:
                    UNREACHABLE;
            }
        }

        uint8_t code = Consume();
        if (code == '\\') {
            auto pre_result = PreParseEscapeSequence();
            std::visit(::utils::Overloaded{process_char, process_char_class}, pre_result);
        } else if (code == '-') {
            THROW_REGEX_PARSER_ERROR_IF(Peek() != ']' || mask_was_extended,
                "Dash `-` can be only first or last symbol in [] without escape sequence.");
        } else if (code == ']') {
            mask.ExtendFrom('-');
            break;
        } else {
            process_char(code);
        }
    }

    THROW_REGEX_PARSER_ERROR_IF(
        negated ? mask.Count() == consts::kStateEdgesCount : mask.Count() == 0,
        "Char set should contain at least one accepted symbol.");
    return std::make_unique<ast::CharSetNode>(mask, negated);
}

std::unique_ptr<ast::Node> Parser::ParseChar() {
    auto char_length = ::utils::GetUtf8CharLength(Peek());
    switch (char_length) {
        case 0:
            THROW_REGEX_PARSER_ERROR("Got invalid utf8 sequence (starts from 0b10... byte).");
        case static_cast<size_t>(-1):
            THROW_REGEX_PARSER_ERROR("Got invalid utf8 sequence (unknown encoding).");
        case 1:
            return ParseSingleChar();
        case 2:
        case 3:
        case 4:
            return ParseWideChar(char_length);
        default:
            UNREACHABLE;
    }
}

std::unique_ptr<ast::Node> Parser::ParseSingleChar() {
    uint8_t ch = Consume();

    switch (ch) {
        case '\\':
            return ParseEscapeSequence();
        case '.':
            return std::make_unique<ast::CharClassNode>(ast::CharClass::NEWLINE, true);
        case '*':
        case '+':
        case '?':
            THROW_REGEX_PARSER_ERROR(
                "Expected char but got unescaped repeat qualifier '" << ch << "'");
        case '(':
        case ')':
        case '|':
            UNREACHABLE;
        default:
            break;
    }
    return std::make_unique<ast::CharNode>(ch);
}

std::variant<uint8_t, Parser::CharClassDesc> Parser::PreParseEscapeSequence() {
    uint8_t ch = ConsumeAsciiChar();
    switch (ch) {
        case 'n':
            return U8('\n');
        case 't':
            return U8('\t');
        case 'r':
            return U8('\r');
        case 'f':
            return U8('\f');
        case 'v':
            return U8('\v');
        case 'x': {
            std::stringstream byte_hex{};
            byte_hex << ConsumeAsciiChar() << ConsumeAsciiChar();
            auto maybe_result = utils::ParseHexByte(byte_hex.str());
            THROW_REGEX_PARSER_ERROR_IF(!maybe_result.has_value(), "Incorrect hex byte.");
            return *maybe_result;
        }
        case 'w':
        case 'W':
            return CharClassDesc{ast::CharClass::WORD, ch == 'W'};
        case 'd':
        case 'D':
            return CharClassDesc{ast::CharClass::DIGIT, ch == 'D'};
        case 's':
        case 'S':
            return CharClassDesc{ast::CharClass::SPACE, ch == 'S'};
        default:
            break;
    }
    return ch;
}

std::unique_ptr<ast::Node> Parser::ParseEscapeSequence() {
    auto pre_result = PreParseEscapeSequence();
    auto process_char = [](uint8_t code) { return std::make_unique<ast::CharNode>(code); };
    auto process_char_class = [](const CharClassDesc& desc) {
        return std::make_unique<ast::CharClassNode>(desc.char_class, desc.negated);
    };
    return std::visit<std::unique_ptr<ast::Node>>(
        ::utils::Overloaded{process_char, process_char_class}, pre_result);
}

std::unique_ptr<ast::Node> Parser::ParseWideChar(size_t char_length) {
    std::string wide_char;
    for (size_t i = 0; i < char_length; ++i) {
        THROW_REGEX_PARSER_ERROR_IF(IsEof(), "Unexpected eof while parsing utf-8 char.");
        uint8_t code = Consume();
        if (i > 0) {
            THROW_REGEX_PARSER_ERROR_IF(
                ::utils::GetUtf8CharLength(code) != 0, "Incorrect utf-8 char.");
        }
        wide_char.push_back(code);
    }
    return std::make_unique<ast::WideCharNode>(wide_char);
}

}  // namespace lib::regex

#undef U8
