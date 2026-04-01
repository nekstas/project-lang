#pragma once

#include <ostream>
#include <string>

#include "../../../lib/errors/errors.h"

#define UNARY_OPERATION_LIST(X) \
    X(NEG, "-")

namespace lang::ast::enums {

enum class UnaryOperation {
#define X(name, symbol) name,
    UNARY_OPERATION_LIST(X)
#undef X
};

inline std::string UnaryOperationToString(UnaryOperation operation) {
    switch (operation) {
#define X(name, symbol) \
    case UnaryOperation::name: \
        return symbol;
        UNARY_OPERATION_LIST(X)
#undef X
        default:
            UNREACHABLE;
    }
}

#undef UNARY_OPERATION_LIST

inline std::ostream& operator<<(std::ostream& out, UnaryOperation operation) {
    return out << UnaryOperationToString(operation);
}

}  // namespace lang::ast::enums
