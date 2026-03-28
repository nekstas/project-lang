#pragma once

#include <sstream>

#include "visitor.h"

namespace lib::regex::visitors {

class Formatter : public Visitor {
public:
    std::string ToString(const ast::Node* node);

    void Visit(const ast::CharNode& node) override;
    void Visit(const ast::WideCharNode& node) override;
    void Visit(const ast::ChoiceNode& node) override;
    void Visit(const ast::RepeatNode& node) override;
    void Visit(const ast::SequenceNode& node) override;

private:
    std::stringstream out_;
};

}  // namespace lib::regex::visitors
