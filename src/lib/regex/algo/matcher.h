#pragma once

#include <string>
#include <ostream>
#include <tuple>

namespace lang::regex::algo {

class Matcher {
public:
    struct Result {
        bool matched = false;
        size_t length = 0;
        size_t final_id = -1;

        bool operator==(const Result& another) const {
            return std::tie(matched, length, final_id) ==
                   std::tie(another.matched, another.length, another.final_id);
        }
    };

public:
    virtual ~Matcher() {}

    virtual Result Match(const std::string& code) = 0;

protected:
    static void UpdateResult(size_t length, size_t final_id, Result& result);
};

}  // namespace lang::regex::algo
