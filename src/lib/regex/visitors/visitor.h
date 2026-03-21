#pragma once

#include "../fwd.h"

namespace lang::regex::visitors {

class Visitor {
public:
    virtual ~Visitor() {}

    virtual void Visit(const lang::regex::ast::CharNode& node) = 0;
    virtual void Visit(const lang::regex::ast::WideCharNode& node) = 0;
    virtual void Visit(const lang::regex::ast::ChoiceNode& node) = 0;
    virtual void Visit(const lang::regex::ast::SequenceNode& node) = 0;
    virtual void Visit(const lang::regex::ast::RepeatNode& node) = 0;
};

}  // namespace lang::regex::visitors
