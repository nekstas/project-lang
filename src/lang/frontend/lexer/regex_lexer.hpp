#pragma once

#include "../../../lib/lang/context/base_context.h"
#include "../../../lib/lang/frontend/lexer/impl/regex_lexer.hpp"
#include "../../enums/token_type.h"

namespace lang::frontend {

template <lib::lang::ContextLike Context>
class RegexLexer : public lib::lang::frontend::impl::RegexLexer<e::TokenType, Context> {
private:
    using Super = lib::lang::frontend::impl::RegexLexer<e::TokenType, Context>;

protected:
    using HasValue = Super::HasValue;

public:
    RegexLexer() {
        FillTokens();
    }

private:
    void FillTokens() {
        Super::Init();

        Super::AddToken(e::TokenType::WHITESPACE, "[ \\t\\r\\f\\v]+");
        Super::AddToken(e::TokenType::NEW_LINE, "\\n");

        Super::AddToken(e::TokenType::COMMA, ",");
        Super::AddToken(e::TokenType::SEMICOLON, ";");

        Super::AddToken(e::TokenType::COLON, ":");
        Super::AddToken(e::TokenType::ARROW, "->");

        Super::AddToken(e::TokenType::LPAREN, "\\(");
        Super::AddToken(e::TokenType::RPAREN, "\\)");
        Super::AddToken(e::TokenType::LBRACE, "\\{");
        Super::AddToken(e::TokenType::RBRACE, "\\}");

        Super::AddToken(e::TokenType::FN_K, "fn");
        Super::AddToken(e::TokenType::LET_K, "let");
        Super::AddToken(e::TokenType::MUT_K, "mut");
        Super::AddToken(e::TokenType::IF_K, "if");
        Super::AddToken(e::TokenType::ELSE_K, "else");
        Super::AddToken(e::TokenType::WHILE_K, "while");
        Super::AddToken(e::TokenType::RETURN_K, "return");

        Super::AddToken(e::TokenType::ASSIGN_O, "=");

        Super::AddToken(e::TokenType::PLUS_O, "\\+");
        Super::AddToken(e::TokenType::MINUS_O, "-");
        Super::AddToken(e::TokenType::STAR_O, "\\*");
        Super::AddToken(e::TokenType::SLASH_O, "/");

        Super::AddToken(e::TokenType::EQ_O, "==");
        Super::AddToken(e::TokenType::NE_O, "!=");
        Super::AddToken(e::TokenType::LT_O, "<");
        Super::AddToken(e::TokenType::LE_O, "<=");
        Super::AddToken(e::TokenType::GT_O, ">");
        Super::AddToken(e::TokenType::GE_O, ">=");

        Super::AddToken(e::TokenType::INT_LITERAL, "\\d+", HasValue::TRUE);
        Super::AddToken(e::TokenType::IDENTIFIER, "[a-zA-Z_]\\w*", HasValue::TRUE);

        Super::Build(e::TokenType::END_OF_FILE);
    }
};

}  // namespace lang::frontend
