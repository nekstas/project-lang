#include "matcher.h"

#include "../../dfa/dfa.h"

namespace lang::regex::algo::dfa {

Matcher::Matcher(const regex::dfa::Dfa& dfa) : dfa_(dfa) {}

Matcher::Result Matcher::Match(const std::string& code) {
    Result result;
    auto current_state = dfa_.GetRootId();
    UpdateResult(0, dfa_.GetState(current_state).GetFinalId(), result);
    for (size_t i = 0; i < code.size(); ++i) {
        current_state = dfa_.GetState(current_state).GetEdge(code[i]);
        if (current_state == -1) {
            break;
        }
        UpdateResult(i + 1, dfa_.GetState(current_state).GetFinalId(), result);
    }
    return result;
}

}  // namespace lang::regex::algo::dfa
