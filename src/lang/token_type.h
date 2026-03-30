#pragma once

#include <ostream>
#include <string>

#include "../lib/errors/errors.h"

#define TOKEN_TYPE_LIST(X) \
    X(END_OF_FILE)         \
    X(NUMBER)

namespace lang {

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

}  // namespace lang
