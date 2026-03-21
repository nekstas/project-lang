#pragma once

#include "../errors/errors.h"
#include "parser/error_state.h"

namespace lang::regex::errors {

class ParserError : public ::errors::RuntimeError {
public:
    ParserError(const std::string& message, const std::string& file, const size_t line,
                const lang::regex::parser::ErrorState& error_state)
        : error_state_(error_state)
        , RuntimeError(utils::FormatStream{} << ConstructMessageFromErrorState() << "\n"
                                             << message,
                       file, line) {}

    std::string ConstructMessageFromErrorState() const {
        utils::FormatStream builder;
        builder << "[*] At pos " << error_state_.GetPos() << " got ";
        if (error_state_.IsEof()) {
            builder << "EOF.";
        } else {
            builder << "'" << error_state_.GetChar() << "'";
        }
        return builder;
    }

private:
    lang::regex::parser::ErrorState error_state_;
};

}  // namespace lang::regex::errors
