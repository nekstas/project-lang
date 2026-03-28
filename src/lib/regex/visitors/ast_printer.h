#pragma once

#include <sstream>

#include "../utils/indentable.h"
#include "visitor.h"

namespace lib::regex::visitors {

class AstPrinter : public utils::Indentable, public Visitor {
public:
    using Indentable::Indentable;

    std::string ToString(const ast::Node* node);

public:
    void Visit(const ast::CharNode& node) override;
    void Visit(const ast::WideCharNode& node) override;
    void Visit(const ast::ChoiceNode& node) override;
    void Visit(const ast::RepeatNode& node) override;
    void Visit(const ast::SequenceNode& node) override;

private:
    void ProcessNodesBaseNode(const ast::NodesBaseNode& node);

private:
    std::stringstream out_;
};

}  // namespace lib::regex::visitors
