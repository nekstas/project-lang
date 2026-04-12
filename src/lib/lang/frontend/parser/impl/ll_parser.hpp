#pragma once

#include "../../../context/base_context.h"
#include "../../../src/token.hpp"
#include "../parser.hpp"

namespace lib::lang::frontend::impl {

template <typename TokenType, typename RuleType, ContextLike Context>
class LLParser : public Parser<TokenType, RuleType, Context> {
private:
    using Super = Parser<TokenType, RuleType, Context>;

public:
    typename Super::NodePtr Run(t::Tokens<TokenType> desc, Context& ctx) const override {
        return nullptr;  // TODO
    }

    std::string Name() const override {
        return "LLParser";
    }

protected:
private:
};

}  // namespace lib::lang::frontend::impl
