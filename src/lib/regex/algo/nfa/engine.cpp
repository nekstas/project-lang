#include "engine.h"

#include <queue>

namespace lang::regex::algo::nfa {

Engine::Engine(const regex::nfa::Nfa& nfa) : nfa_(nfa), eps_closures_(nfa_.Size()) {
    Build();
}

const regex::nfa::Nfa& Engine::GetNfa() const {
    return nfa_;
}

std::set<size_t> Engine::GetRootIds() const {
    return EpsClosure(nfa_.GetRootId());
}

const std::set<size_t>& Engine::EpsClosure(size_t state_id) const {
    return eps_closures_[state_id];
}

std::set<size_t> Engine::EpsClosure(const std::set<size_t>& state_ids) const {
    std::set<size_t> result;
    for (size_t state_id : state_ids) {
        result.insert(eps_closures_[state_id].begin(), eps_closures_[state_id].end());
    }
    return result;
}

std::set<uint8_t> Engine::GetEdgeCodes(const std::set<size_t>& state_ids) const {
    std::set<uint8_t> result;
    for (size_t state_id : state_ids) {
        const auto codes = nfa_.GetState(state_id).GetEdgeCodes();
        result.insert(codes.begin(), codes.end());
    }
    return result;
}

std::set<size_t> Engine::Move(const std::set<size_t>& state_ids, uint8_t code) const {
    std::set<size_t> result;
    for (size_t state_id : state_ids) {
        auto another_state_id = nfa_.GetState(state_id).GetEdge(code);
        if (another_state_id != -1) {
            result.insert(another_state_id);
        }
    }
    return result;
}

std::set<size_t> Engine::MoveClosure(const std::set<size_t>& state_ids, uint8_t code) const {
    return EpsClosure(Move(state_ids, code));
}

size_t Engine::GetFinalId(const std::set<size_t>& state_ids) const {
    size_t final_id = -1;
    for (size_t state_id : state_ids) {
        final_id = std::min(final_id, nfa_.GetState(state_id).GetFinalId());
    }
    return final_id;
}

void Engine::Build() {
    for (size_t state_id = 0; state_id < nfa_.Size(); ++state_id) {
        BuildForState(state_id);
    }
}

void Engine::BuildForState(size_t state_id) {
    // Assume for every another_state_id < state_id
    // eps_closures_[another_state_id] already calculated
    std::queue<size_t> queue;
    queue.push(state_id);
    eps_closures_[state_id].insert(state_id);

    while (!queue.empty()) {
        const auto another_state_id = queue.front();
        queue.pop();

        if (another_state_id < state_id) {
            eps_closures_[state_id].insert(eps_closures_[another_state_id].begin(),
                                           eps_closures_[another_state_id].end());
        } else {
            for (size_t edge_id : nfa_.GetState(another_state_id).GetEpsEdges()) {
                if (!eps_closures_[state_id].contains(edge_id)) {
                    eps_closures_[state_id].insert(edge_id);
                    queue.push(edge_id);
                }
            }
        }
    }
}

}  // namespace lang::regex::algo::nfa