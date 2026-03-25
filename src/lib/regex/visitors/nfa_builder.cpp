#include "nfa_builder.h"

#include "../../errors/errors.h"
#include "../ast/all.h"
#include "../nfa/nfa.h"

namespace lang::regex::visitors {

NfaBuilder::NfaBuilder() : data_(), last_state_(data_.GetRoot()) {}

lang::regex::nfa::Nfa NfaBuilder::GetNfa() const {
    return lang::regex::nfa::Nfa{data_.GetData()};
}

size_t NfaBuilder::ExtendFromAst(const lang::regex::ast::Node& node) {
    last_state_ = data_.GetRoot();
    node.Accept(*this);
    return last_state_.MakeFinal();
}

void NfaBuilder::Clear() {
    data_.Clear();
    last_state_ = data_.GetRoot();
}

void NfaBuilder::Visit(const lang::regex::ast::CharNode& node) {
    last_state_ = last_state_.AddEdge(node.GetCode());
}

void NfaBuilder::Visit(const lang::regex::ast::WideCharNode& node) {
    for (uint8_t part : node.GetWideChar()) {
        last_state_ = last_state_.AddEdge(part);
    }
}

void NfaBuilder::Visit(const lang::regex::ast::ChoiceNode& node) {
    auto start_state = last_state_;

    std::vector<lang::regex::nfa::StateWrapper> last_states;
    for (const auto& alt_node : node.GetNodes()) {
        last_state_ = start_state.AddEpsEdge();
        alt_node->Accept(*this);
        last_states.push_back(last_state_);
    }

    last_state_ = data_.CreateState();
    for (auto& state : last_states) {
        state.AddEpsEdgeTo(last_state_);
    }
}

void NfaBuilder::Visit(const lang::regex::ast::RepeatNode& node) {
    switch (node.GetRepeatType()) {
        case ast::RepeatType::ZERO_OR_MORE:
            VisitZeroOrMoreRepeatNode(node.GetNode());
            break;
        case ast::RepeatType::ONE_OR_MORE:
            VisitOneOrMoreRepeatNode(node.GetNode());
            break;
        case ast::RepeatType::ZERO_OR_ONE:
            VisitZeroOrOneRepeatNode(node.GetNode());
            break;
        default:
            UNREACHABLE;
    }
}

void NfaBuilder::Visit(const lang::regex::ast::SequenceNode& node) {
    for (const auto& another_node : node.GetNodes()) {
        another_node->Accept(*this);
    }
}

void NfaBuilder::VisitZeroOrMoreRepeatNode(const ast::Node& inner_node) {
    auto repeat_states = MakeRepeatStates(inner_node);
    repeat_states.end_inner_state.AddEpsEdgeTo(repeat_states.start_inner_state);
    repeat_states.start_state.AddEpsEdgeTo(repeat_states.end_state);
}

void NfaBuilder::VisitOneOrMoreRepeatNode(const ast::Node& inner_node) {
    auto repeat_states = MakeRepeatStates(inner_node);
    repeat_states.end_inner_state.AddEpsEdgeTo(repeat_states.start_inner_state);
}

void NfaBuilder::VisitZeroOrOneRepeatNode(const ast::Node& inner_node) {
    auto repeat_states = MakeRepeatStates(inner_node);
    repeat_states.start_state.AddEpsEdgeTo(repeat_states.end_state);
}

NfaBuilder::RepeatStates NfaBuilder::MakeRepeatStates(const ast::Node& inner_node) {
    NfaBuilder::RepeatStates result;
    result.start_state = last_state_;
    result.start_inner_state = last_state_ = result.start_state.AddEpsEdge();
    inner_node.Accept(*this);
    result.end_inner_state = last_state_;
    result.end_state = result.end_inner_state.AddEpsEdge();
    return result;
}

}  // namespace lang::regex::visitors
