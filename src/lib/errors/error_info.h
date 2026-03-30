#pragma once

#include <string>

namespace errors {

struct ErrorInfo {
    std::string message;
    std::string error_cls_name;
    std::string file;
    size_t line;
};

}  // namespace errors
