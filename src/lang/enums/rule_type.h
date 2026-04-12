#pragma once

#include <ostream>
#include <string>

#include "../../lib/errors/errors.h"

#define RULE_TYPE_LIST(X) X(IntLiteral)

namespace lang::e {

enum class RuleType {
#define X(name) name,
    RULE_TYPE_LIST(X)
#undef X
};

inline std::string RuleTypeToString(RuleType rule_type) {
    switch (rule_type) {
#define X(name)          \
    case RuleType::name: \
        return #name;
        RULE_TYPE_LIST(X)
#undef X
        default:
            UNREACHABLE;
    }
}

#undef RULE_TYPE_LIST

inline std::ostream& operator<<(std::ostream& out, RuleType token_type) {
    return out << RuleTypeToString(token_type);
}

}  // namespace lang::enums
