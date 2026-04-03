#pragma once

#include <vector>

#include "src/token.hpp"

namespace lib::lang::t {

template <typename TokenType>
using Token = src::Token<TokenType>;

template <typename TokenType>
using Tokens = std::vector<Token<TokenType>>;

}  // namespace lib::lang::t
