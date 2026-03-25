#pragma once

#include "../fwd.h"
#include "../nfa/data_wrapper.h"
#include "../nfa/state_wrapper.h"
#include "visitor.h"

namespace lang::regex::visitors {

class NfaBuilder : public Visitor {
private:
    struct RepeatStates {
        lang::regex::nfa::StateWrapper start_state;
        lang::regex::nfa::StateWrapper start_inner_state;
        lang::regex::nfa::StateWrapper end_inner_state;
        lang::regex::nfa::StateWrapper end_state;
    };

public:
    NfaBuilder();

    lang::regex::nfa::Nfa GetNfa() const;
    size_t ExtendFromAst(const lang::regex::ast::Node& node);
    void Clear();

    void Visit(const lang::regex::ast::CharNode& node) override;
    void Visit(const lang::regex::ast::WideCharNode& node) override;
    void Visit(const lang::regex::ast::ChoiceNode& node) override;
    void Visit(const lang::regex::ast::RepeatNode& node) override;
    void Visit(const lang::regex::ast::SequenceNode& node) override;

private:
    void VisitZeroOrMoreRepeatNode(const lang::regex::ast::Node& inner_node);
    void VisitOneOrMoreRepeatNode(const lang::regex::ast::Node& inner_node);
    void VisitZeroOrOneRepeatNode(const lang::regex::ast::Node& inner_node);

private:
    RepeatStates MakeRepeatStates(const lang::regex::ast::Node& inner_node);

private:
    lang::regex::nfa::DataWrapper data_;
    lang::regex::nfa::StateWrapper last_state_;
};

}  // namespace lang::regex::visitors
