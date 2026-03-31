#pragma once

#include <ostream>
#include <string>

#include "../../../lib/errors/errors.h"
#include "../../token_type.h"

#define BINARY_OPERATION_LIST(X) \
    X(SUM, "+", PLUS_O)          \
    X(SUB, "-", MINUS_O)         \
    X(MUL, "*", STAR_O)          \
    X(DIV, "/", SLASH_O)         \
    X(EQ, "==", EQ_O)            \
    X(NE, "!=", NE_O)            \
    X(LT, "<", LT_O)             \
    X(LE, "<=", LE_O)            \
    X(GT, ">", GT_O)             \
    X(GE, ">=", GE_O)

namespace lang::ast::enums {

enum class BinaryOperation {
#define X(name, symbol, token) name,
    BINARY_OPERATION_LIST(X)
#undef X
};

inline std::string BinaryOperationToString(BinaryOperation operation) {
    switch (operation) {
#define X(name, symbol, token)  \
    case BinaryOperation::name: \
        return symbol;
        BINARY_OPERATION_LIST(X)
#undef X
        default:
            UNREACHABLE;
    }
}

inline BinaryOperation TokenTypeToBinaryOperation(TokenType token_type) {
    switch (token_type) {
#define X(name, symbol, token) \
    case TokenType::token:     \
        return BinaryOperation::name;
        BINARY_OPERATION_LIST(X)
#undef X
        default:
            UNREACHABLE;
    }
}

#undef TOKEN_TYPE_LIST

inline std::ostream& operator<<(std::ostream& out, BinaryOperation operation) {
    return out << BinaryOperationToString(operation);
}

}  // namespace lang::ast::enums
