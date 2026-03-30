#include "errors.h"

namespace lib::regex::errors {

ParserError::ParserError(const ::errors::ErrorInfo& info, const parser::ErrorState& error_state)
    : RuntimeError(::errors::ErrorInfo{utils::FormatStream{}
                                           << ConstructMessageFromErrorState(error_state) << "\n"
                                           << info.message,
          info.error_cls_name, info.file, info.line})
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

}  // namespace lib::regex::errors
