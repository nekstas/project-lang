#pragma once

#include "../fwd.h"

namespace lib::regex::visitors {

class Visitor {
public:
    virtual ~Visitor() {}

    virtual void Visit(const ast::CharNode& node) = 0;
    virtual void Visit(const ast::WideCharNode& node) = 0;
    virtual void Visit(const ast::ChoiceNode& node) = 0;
    virtual void Visit(const ast::SequenceNode& node) = 0;
    virtual void Visit(const ast::RepeatNode& node) = 0;
    virtual void Visit(const ast::CharSetNode& node) = 0;
    virtual void Visit(const ast::CharClassNode& node) = 0;
};

}  // namespace lib::regex::visitors
