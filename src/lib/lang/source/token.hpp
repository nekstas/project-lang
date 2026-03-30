#pragma once

#include <iomanip>
#include <string>

#include "span.h"

namespace lib::lang::source {

template <typename TokenType>
class Token {
public:
    Token(TokenType type, const Span& span) : type_(type), span_(span) {}

    Token(TokenType type, const std::string& value, const Span& span)
        : type_(type), value_(value), span_(span) {}

    TokenType GetType() const {
        return type_;
    }

    bool HasValue() const {
        return !value_.empty();
    }

    const std::string& GetValue() const {
        return value_;
    }

    const Span& GetSpan() const {
        return span_;
    }

protected:
    TokenType type_;
    std::string value_;
    Span span_;
};

template <typename TokenType>
std::ostream& operator<<(std::ostream& out, const Token<TokenType>& token) {
    out << "<" << token.GetType();
    if (token.HasValue()) {
        out << ":" << std::quoted(token.GetValue());
    }
    return out << ">";
}

}  // namespace lib::lang::source
