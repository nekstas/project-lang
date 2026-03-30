#pragma once

#include <vector>

#include "../source/token.hpp"

namespace lib::lang::frontend {

template <typename TokenType>
using Tokens = std::vector<source::Token<TokenType>>;

}
