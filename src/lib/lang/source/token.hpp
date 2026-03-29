#pragma once

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

}  // namespace lib::lang::source
