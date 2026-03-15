#pragma once

#include <cassert>
#include <sstream>

#include "../utils/indentable.h"
#include "visitor.h"

namespace lang::regex::visitors {

class AstPrinter : public lang::regex::utils::Indentable, public Visitor {
public:
    using lang::regex::utils::Indentable::Indentable;

    std::string ToString(lang::regex::ast::Node* node);

public:
    void Visit(const lang::regex::ast::CharNode& node) override;
    void Visit(const lang::regex::ast::ChoiceNode& node) override;
    void Visit(const lang::regex::ast::SequenceNode& node) override;
    void Visit(const lang::regex::ast::RepeatNode& node) override;

private:
    void ProcessNodesBaseNode(const lang::regex::ast::NodesBaseNode& node);

private:
    std::stringstream out_;
};

}  // namespace lang::regex::visitors
