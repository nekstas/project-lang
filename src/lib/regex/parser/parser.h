#pragma once

#include <memory>
#include <string>

#include "../ast/node.h"
#include "parser_base.h"

namespace lib::regex {

class Parser : public parser::Base {
public:
    std::unique_ptr<ast::Node> Parse(const std::string& code);

private:
    std::unique_ptr<ast::Node> Parse();
    std::unique_ptr<ast::Node> ParseSequence();
    std::unique_ptr<ast::Node> ParseRepeat();
    std::unique_ptr<ast::Node> ParseChoice();
    std::unique_ptr<ast::Node> ParseChar();
    std::unique_ptr<ast::Node> ParseSingleChar();
    std::unique_ptr<ast::Node> ParseWideChar(size_t char_length);
};

}  // namespace lib::regex
