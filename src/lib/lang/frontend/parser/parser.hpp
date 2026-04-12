#pragma once

#include <memory>

#include "../../../flow/typed_stage.hpp"
#include "../../context/base_context.h"
#include "../../cst/node.hpp"
#include "../../types.hpp"

namespace lib::lang::frontend {

template <typename TokenType, typename RuleType, ContextLike Context>
class Parser : public flow::TypedStage<Parser<TokenType, RuleType, Context>, Context,
                   t::Tokens<TokenType>, std::unique_ptr<cst::Node<TokenType, RuleType>>> {
public:
    using NodeType = cst::Node<TokenType, RuleType>;
    using NodePtr = std::unique_ptr<NodeType>;

public:
    virtual std::unique_ptr<cst::Node<TokenType, RuleType>> Run(
        t::Tokens<TokenType> tokens, Context& ctx) const = 0;
};

}  // namespace lib::lang::frontend
