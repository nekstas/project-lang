#include "matcher.h"

namespace lib::regex::algo::nfa {

Matcher::Matcher(const regex::nfa::Nfa& nfa) : engine_(nfa) {}

Matcher::Result Matcher::Match(const std::string& code) {
    Result result;
    auto current_state = engine_.EpsClosure(engine_.GetNfa().GetRootId());
    UpdateResult(0, engine_.GetFinalId(current_state), result);

    for (size_t i = 0; i < code.size(); ++i) {
        current_state = engine_.EpsClosure(engine_.Move(current_state, code[i]));
        UpdateResult(i + 1, engine_.GetFinalId(current_state), result);
    }
    return result;
}

}  // namespace lib::regex::algo::nfa
