#pragma once

#include "../src/span.h"
#include "context.h"

namespace lib::lang::render {

class Span {
    friend std::ostream& operator<<(std::ostream& out, const Span& item);

public:
    Span(const std::string& message, const src::Span& span, const Context& ctx)
        : message_(message), span_(span), ctx_(ctx) {}

private:
    std::string message_;
    src::Span span_;
    const Context& ctx_;
};

std::ostream& operator<<(std::ostream& out, const Span& item);

}  // namespace lib::lang::render
