#include "errors.h"

namespace lang::regex::errors {

ParserError::ParserError(const std::string& message, const std::string& error_cls_name,
                         const std::string& file, size_t line,
                         const parser::ErrorState& error_state)
    : RuntimeError(utils::FormatStream{} << ConstructMessageFromErrorState(error_state) << "\n"
                                         << message,
                   error_cls_name, file, line)
    , error_state_(error_state) {}

std::string ParserError::ConstructMessageFromErrorState(const parser::ErrorState& error_state) {
    utils::FormatStream builder;
    builder << "[*] At pos " << error_state.GetPos() << " got ";
    if (error_state.IsEof()) {
        builder << "EOF.";
    } else {
        builder << "'" << error_state.GetChar() << "'";
    }
    return builder;
}

}  // namespace lang::regex::errors
