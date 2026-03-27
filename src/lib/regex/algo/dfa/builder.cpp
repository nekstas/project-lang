#include "builder.h"

#include <map>
#include <queue>

#include "../../../utils/utils.h"
#include "../../dfa/dfa.h"
#include "../../dfa/dfa_wrapper.h"
#include "../../dfa/state_wrapper.h"
#include "../../errors.h"
#include "../nfa/engine.h"

namespace lang::regex::algo::dfa {

namespace {

class Impl {
public:
    explicit Impl(const regex::nfa::Nfa& nfa) : engine(nfa) {}

    regex::dfa::Dfa Build() {
        VisitNewStateIfNecessary(engine.GetRootIds());

        while (!queue_.empty()) {
            const auto state_ids = queue_.Extract();
            auto new_state = MarkFinal(state_ids);

            for (uint8_t code : engine.GetEdgeCodes(state_ids)) {
                const auto another_state_ids = engine.MoveClosure(state_ids, code);
                VisitNewStateIfNecessary(another_state_ids);
                new_state.AddEdgeTo(code, GetNewState(another_state_ids));
            }
        }

        EnsureAllFinalIdsUsed();
        return dfa_wrapper_.GetFa();
    }

    void VisitNewStateIfNecessary(const std::set<size_t>& state_ids) {
        if (to_new_state_id_.contains(state_ids)) {
            return;
        }
        to_new_state_id_[state_ids] = dfa_wrapper_.CreateState().GetStateId();
        queue_.push(state_ids);
    }

    regex::dfa::StateWrapper GetNewState(const std::set<size_t>& state_ids) {
        return dfa_wrapper_.GetState(to_new_state_id_.at(state_ids));
    }

    regex::dfa::StateWrapper MarkFinal(const std::set<size_t>& state_ids) {
        auto new_state = GetNewState(state_ids);
        size_t final_id = engine.GetFinalId(state_ids);
        new_state.SetFinalId(final_id);
        if (final_id != -1) {
            final_ids_.insert(final_id);
        }
        return new_state;
    }

    void EnsureAllFinalIdsUsed() {
        THROW_IF(final_ids_.size() != engine.GetNfa().GetFinalStatesNumber(),
                 lang::regex::errors::DfaBuilderError,
                 "There are " << final_ids_.size()
                              << " final states in created Dfa, but there were "
                              << engine.GetNfa().GetFinalStatesNumber()
                              << " final states in given Nfa. (Some old final states can't be "
                                 "achieved in new Nfa.)");
        dfa_wrapper_.SetFinalStatesNumber(final_ids_.size());
    }

private:
    nfa::Engine engine;
    regex::dfa::DfaWrapper dfa_wrapper_;
    std::map<std::set<size_t>, size_t> to_new_state_id_;
    utils::BetterQueue<std::set<size_t>> queue_;
    std::unordered_set<size_t> final_ids_;
};

}  // namespace

regex::dfa::Dfa Builder::Build(const regex::nfa::Nfa& nfa) {
    return Impl(nfa).Build();
}

}  // namespace lang::regex::algo::dfa
