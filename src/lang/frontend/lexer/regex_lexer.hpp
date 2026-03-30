#pragma once

#include "../../../lib/lang/context/base_context.h"
#include "../../../lib/lang/frontend/lexer/impl/regex_lexer.hpp"
#include "../../token_type.h"

namespace lang::frontend {

template <lib::lang::ContextLike Context>
class RegexLexer : public lib::lang::frontend::impl::RegexLexer<TokenType, Context> {
private:
    using Super = lib::lang::frontend::impl::RegexLexer<TokenType, Context>;

protected:
    using HasValue = Super::HasValue;

public:
    RegexLexer() {
        FillTokens();
    }

private:
    void FillTokens() {
        Super::Init();
        Super::AddToken(TokenType::NUMBER, "\\d+", HasValue::TRUE);
        Super::Build(TokenType::END_OF_FILE);
    }
};

}  // namespace lang::frontend
