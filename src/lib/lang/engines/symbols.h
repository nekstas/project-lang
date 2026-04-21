#pragma once

#include <memory>
#include <vector>

#include "../symbols/scope.h"

namespace lib::lang::engines {

class Symbols {
public:
    template <typename ScopeType, typename... Args>
    ScopeType* AddScope(Args&&... args) {
        auto scope = AddScope(std::make_unique<ScopeType>(std::forward<Args>(args)...));
        return dynamic_cast<ScopeType*>(scope);
    }

    symbols::Scope* AddScope(std::unique_ptr<symbols::Scope> scope);

private:
    std::vector<std::unique_ptr<symbols::Scope>> scopes_;
};

}  // namespace lib::lang::engines
