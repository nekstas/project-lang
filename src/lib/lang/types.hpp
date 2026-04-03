#pragma once

#include <vector>

#include "source/token.hpp"

namespace lib::lang::t {

template <typename TokenType>
using Token = source::Token<TokenType>;

template <typename TokenType>
using Tokens = std::vector<Token<TokenType>>;

}  // namespace lib::lang::t
