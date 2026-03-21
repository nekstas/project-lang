#pragma once

#include <sstream>

#include "visitor.h"

namespace lang::regex::visitors {

class Formatter : public Visitor {
public:
    std::string ToString(const lang::regex::ast::Node* node);

    void Visit(const lang::regex::ast::CharNode& node) override;
    void Visit(const lang::regex::ast::WideCharNode& node) override;
    void Visit(const lang::regex::ast::ChoiceNode& node) override;
    void Visit(const lang::regex::ast::RepeatNode& node) override;
    void Visit(const lang::regex::ast::SequenceNode& node) override;

private:
    std::stringstream out_;
};

}  // namespace lang::regex::visitors
