#pragma once

#include <sstream>

namespace utils {

class FormatStream : public std::stringstream {
public:
    operator std::string() const {
        return str();
    }
};

}
