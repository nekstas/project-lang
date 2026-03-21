#include "parser.h"

#include "../../utils/utils.h"
#include "../ast/all.h"
#include "../utils/utils.h"

namespace lang::regex {

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
        THROW_REGEX_PARSER_ERROR_IF(ast::CastNode<ast::RepeatNode>(result.get()),
                                    "Repeat can't be inside another repeat.");

        const auto repeat_type = ast::RepeatCharToType(Consume());
        result = std::make_unique<ast::RepeatNode>(std::move(result), repeat_type);
    }

    THROW_REGEX_PARSER_ERROR_IF(::utils::IsIn(Peek(), kPossibleRepeatChars),
                                "Multiple repeat modifiers are unsupported.");

    return result;
}

std::unique_ptr<ast::Node> Parser::ParseChoice() {
    if (Peek() != '(') {
        return ParseChar();
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

std::unique_ptr<ast::Node> Parser::ParseChar() {
    const auto char_length = utils::GetUtf8CharLength(Peek());
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
            ch = Consume();
            switch (ch) {
                case 'n':
                    ch = '\n';
                    break;
                case 't':
                    ch = '\t';
                    break;
            }
            break;
        case '*':
        case '+':
        case '?':
            THROW_REGEX_PARSER_ERROR("Expected char but got unescaped repeat qualifier '" << ch
                                                                                          << "'");
        case '(':
        case ')':
        case '|':
            UNREACHABLE;
    }
    return std::make_unique<ast::CharNode>(ch);
}

std::unique_ptr<ast::Node> Parser::ParseWideChar(size_t char_length) {
    std::string wide_char;
    for (size_t i = 0; i < char_length; ++i) {
        wide_char.push_back(Consume());
    }
    return std::make_unique<ast::WideCharNode>(wide_char);
}

}  // namespace lang::regex
