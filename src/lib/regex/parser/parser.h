#pragma once

#include <memory>
#include <string>
#include <variant>

#include "../ast/char_class_node.h"
#include "../ast/node.h"
#include "parser_base.h"

namespace lib::regex {

class Parser : public parser::Base {
private:
    struct CharClassDesc {
        ast::CharClass char_class;
        bool negated;
    };

public:
    std::unique_ptr<ast::Node> Parse(const std::string& code);

private:
    std::unique_ptr<ast::Node> Parse();
    std::unique_ptr<ast::Node> ParseSequence();
    std::unique_ptr<ast::Node> ParseRepeat();
    std::unique_ptr<ast::Node> ParseChoice();
    std::unique_ptr<ast::Node> ParseCharSet();
    std::unique_ptr<ast::Node> ParseChar();
    std::unique_ptr<ast::Node> ParseSingleChar();
    std::unique_ptr<ast::Node> ParseEscapeSequence();
    std::unique_ptr<ast::Node> ParseWideChar(size_t char_length);

private:
    std::variant<uint8_t, CharClassDesc> PreParseEscapeSequence();
};

}  // namespace lib::regex
