#pragma once

#include "../../../lib/lang/context/base_context.h"
#include "../../../lib/lang/frontend/lexer/impl/regex_lexer.hpp"
#include "../../token_type.h"

namespace lang::frontend {

template <lib::lang::ContextLike Context>
class RegexLexer : public lib::lang::frontend::impl::RegexLexer<TokenType, Context> {
private:
    using Super = lib::lang::frontend::impl::RegexLexer<TokenType, Context>;

protected:
    using HasValue = Super::HasValue;

public:
    RegexLexer() {
        FillTokens();
    }

private:
    void FillTokens() {
        Super::Init();

        Super::AddToken(TokenType::WHITESPACE, "[ \\t\\r\\f\\v]+");
        Super::AddToken(TokenType::NEW_LINE, "\\n");

        Super::AddToken(TokenType::COMMA, ",");
        Super::AddToken(TokenType::SEMICOLON, ";");

        Super::AddToken(TokenType::COLON, ":");
        Super::AddToken(TokenType::ARROW, "->");

        Super::AddToken(TokenType::LPAREN, "\\(");
        Super::AddToken(TokenType::RPAREN, "\\)");
        Super::AddToken(TokenType::LBRACE, "\\{");
        Super::AddToken(TokenType::RBRACE, "\\}");

        Super::AddToken(TokenType::FN_K, "fn");
        Super::AddToken(TokenType::LET_K, "let");
        Super::AddToken(TokenType::MUT_K, "mut");
        Super::AddToken(TokenType::IF_K, "if");
        Super::AddToken(TokenType::ELSE_K, "else");
        Super::AddToken(TokenType::WHILE_K, "while");
        Super::AddToken(TokenType::RETURN_K, "return");

        Super::AddToken(TokenType::ASSIGN_O, "=");

        Super::AddToken(TokenType::PLUS_O, "\\+");
        Super::AddToken(TokenType::MINUS_O, "-");

        Super::AddToken(TokenType::EQ_O, "==");
        Super::AddToken(TokenType::NE_O, "!=");
        Super::AddToken(TokenType::LT_O, "<");
        Super::AddToken(TokenType::LE_O, "<=");
        Super::AddToken(TokenType::GT_O, ">");
        Super::AddToken(TokenType::GE_O, ">=");

        Super::AddToken(TokenType::NUMBER, "\\d+", HasValue::TRUE);
        Super::AddToken(TokenType::IDENTIFIER, "[a-zA-Z_]\\w*", HasValue::TRUE);

        Super::Build(TokenType::END_OF_FILE);
    }
};

}  // namespace lang::frontend
