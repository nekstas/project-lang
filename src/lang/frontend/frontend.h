#pragma once

#include "../../lib/lang/context/base_context.h"
#include "../../lib/lang/frontend/file_reader/file_reader.hpp"
#include "lexer/regex_lexer.hpp"
#include "parser/recursive_descent_parser.hpp"
#include "tokens_filter/tokens_filter.hpp"

namespace lang::frontend {

using Token = lib::lang::t::Token<e::TokenType>;
using Tokens = lib::lang::t::Tokens<e::TokenType>;

template <lib::lang::ContextLike Context>
using ReadFile = lib::lang::frontend::FileReader<Context>;

template <lib::lang::ContextLike Context>
using Lexer = RegexLexer<Context>;

template <lib::lang::ContextLike Context>
using TokensFilter = SimpleTokensFilter<Context>;

template <lib::lang::ContextLike Context>
using Parser = RecursiveDescentParser<Context>;

}  // namespace lang::frontend
