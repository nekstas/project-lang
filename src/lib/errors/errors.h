#pragma once

#include <stdexcept>

#include "../utils/format_stream.h"

namespace errors {

#define THROW(error_class, format_expr) throw (error_class)(utils::FormatStream() << format_expr)

class LogicError : public std::logic_error {
public:
    using std::logic_error::logic_error;
};

}
