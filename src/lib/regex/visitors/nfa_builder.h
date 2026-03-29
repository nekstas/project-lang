#pragma once

#include "../fwd.h"
#include "../nfa/nfa_wrapper.h"
#include "../nfa/state_wrapper.h"
#include "visitor.h"

namespace lib::regex::visitors {

class NfaBuilder : public Visitor {
private:
    struct RepeatStates {
        nfa::StateWrapper start_state;
        nfa::StateWrapper start_inner_state;
        nfa::StateWrapper end_inner_state;
        nfa::StateWrapper end_state;
    };

public:
    NfaBuilder();

    nfa::Nfa GetNfa() const;
    size_t ExtendFromAst(const ast::Node& node);
    void Clear();

    void Visit(const ast::CharNode& node) override;
    void Visit(const ast::WideCharNode& node) override;
    void Visit(const ast::ChoiceNode& node) override;
    void Visit(const ast::RepeatNode& node) override;
    void Visit(const ast::SequenceNode& node) override;
    void Visit(const ast::CharSetNode& node) override;
    void Visit(const ast::CharClassNode& node) override;

private:
    void VisitZeroOrMoreRepeatNode(const ast::Node& inner_node);
    void VisitOneOrMoreRepeatNode(const ast::Node& inner_node);
    void VisitZeroOrOneRepeatNode(const ast::Node& inner_node);

private:
    RepeatStates MakeRepeatStates(const ast::Node& inner_node);

private:
    nfa::NfaWrapper nfa_;
    nfa::StateWrapper last_state_;
};

}  // namespace lib::regex::visitors
