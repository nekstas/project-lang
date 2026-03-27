#pragma once

#include "../../dfa/dfa.h"
#include "../matcher.h"

namespace lang::regex::algo::dfa {

class Matcher : public algo::Matcher {
public:
    explicit Matcher(const regex::dfa::Dfa& dfa);

    Result Match(const std::string& code) override;

private:
    regex::dfa::Dfa dfa_;
};

}  // namespace lang::regex::algo::dfa
