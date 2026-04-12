#pragma once

#include <ostream>
#include <string>

#include "../../lib/errors/errors.h"

#define TOKEN_TYPE_LIST(X) \
    X(END_OF_FILE)         \
                           \
    X(WHITESPACE)          \
    X(NEW_LINE)            \
                           \
    X(COMMA)               \
    X(SEMICOLON)           \
                           \
    X(COLON)               \
    X(ARROW)               \
                           \
    X(LPAREN)              \
    X(RPAREN)              \
    X(LBRACE)              \
    X(RBRACE)              \
                           \
    X(FN_K)                \
    X(LET_K)               \
    X(MUT_K)               \
    X(IF_K)                \
    X(ELSE_K)              \
    X(WHILE_K)             \
    X(RETURN_K)            \
                           \
    X(ASSIGN_O)            \
                           \
    X(PLUS_O)              \
    X(MINUS_O)             \
    X(STAR_O)              \
    X(SLASH_O)             \
                           \
    X(EQ_O)                \
    X(NE_O)                \
    X(LT_O)                \
    X(GT_O)                \
    X(LE_O)                \
    X(GE_O)                \
                           \
    X(INT_LITERAL)         \
    X(IDENTIFIER)

namespace lang::e {

enum class TokenType {
#define X(name) name,
    TOKEN_TYPE_LIST(X)
#undef X
};

inline std::string TokenTypeToString(TokenType token_type) {
    switch (token_type) {
#define X(name)           \
    case TokenType::name: \
        return #name;
        TOKEN_TYPE_LIST(X)
#undef X
        default:
            UNREACHABLE;
    }
}

#undef TOKEN_TYPE_LIST

inline std::ostream& operator<<(std::ostream& out, TokenType token_type) {
    return out << TokenTypeToString(token_type);
}

}  // namespace lang::enums
