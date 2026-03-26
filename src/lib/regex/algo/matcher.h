#pragma once

#include <cstddef>
#include <string>

namespace lang::regex::algo {

class Matcher {
public:
    struct Result {
        bool matched;
        size_t length;
        size_t final_id;
    };

public:
    virtual ~Matcher() {}

    virtual Result Match(const std::string& code) = 0;
};

}  // namespace lang::regex::algo
