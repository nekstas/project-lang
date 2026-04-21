#include "symbols.h"

#include "../symbols/scopes/function_scope.h"

namespace lib::lang::engines {

symbols::Scope* Symbols::AddScope(std::unique_ptr<symbols::Scope> scope) {
    scopes_.emplace_back(std::move(scope));
    return scopes_.back().get();
}

}  // namespace lib::lang::engines
