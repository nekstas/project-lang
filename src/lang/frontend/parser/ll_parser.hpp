#pragma once

#include "../../../lib/lang/context/base_context.h"
#include "../../../lib/lang/frontend/parser/impl/ll_parser.hpp"
#include "../../enums/rule_type.h"
#include "../../enums/token_type.h"

namespace lang::frontend {

template <lib::lang::ContextLike Context>
class LLParser : public lib::lang::frontend::impl::LLParser<e::TokenType, e::RuleType, Context> {
private:
    using Super = lib::lang::frontend::impl::LLParser<e::TokenType, e::RuleType, Context>;

public:
    LLParser() {
        // TODO
    }

private:
};

}  // namespace lang::frontend
