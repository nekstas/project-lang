#pragma once

#include <sstream>

#include "../../../lib/utils/indentable.h"
#include "../../fwd.h"
#include "../visitor.h"

namespace lang::hlir::visitors {

class HlirPrinter : public ::utils::Indentable, public Visitor {
public:
    using Indentable::Indentable;

    std::string ToString(const Node* node);

public:
    void Visit(const expr::lit::IntLiteral& lit) override;

private:
    std::stringstream out_;
};

}  // namespace lang::hlir::visitors
