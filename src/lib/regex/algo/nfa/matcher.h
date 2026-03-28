#pragma once

#include "../../fwd.h"
#include "../matcher.h"
#include "engine.h"

namespace lib::regex::algo::nfa {

class Matcher : public algo::Matcher {
public:
    explicit Matcher(const regex::nfa::Nfa& nfa);

    Result Match(const std::string& code) override;

private:
    Engine engine_;
};

}  // namespace lib::regex::algo::nfa
