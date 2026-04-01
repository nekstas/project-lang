#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "../../lib/errors/errors.h"
#include "../../lib/utils/format_stream.h"

namespace lang::limits {

class KeyValueMap {
public:
    using ValueType = std::int64_t;
    using MapType = std::unordered_map<std::string, ValueType>;

    void Set(const std::string& key, ValueType value) {
        values_[key] = value;
    }

    bool Has(const std::string& key) const {
        return values_.contains(key);
    }

    std::optional<ValueType> Get(const std::string& key) const {
        if (!values_.contains(key)) {
            return std::nullopt;
        }
        return values_.at(key);
    }

    ValueType GetOrDefault(const std::string& key, ValueType default_value = 0) const {
        if (!values_.contains(key)) {
            return default_value;
        }
        return values_.at(key);
    }

    void Increment(const std::string& key, ValueType delta = 1) {
        values_[key] += delta;
    }

    const MapType& Data() const {
        return values_;
    }

private:
    MapType values_;
};

using LimitsMap = KeyValueMap;
using CounterMap = KeyValueMap;

inline constexpr char kMaxStaticFunctions[] = "max-static-functions";
inline constexpr char kMaxStaticParameters[] = "max-static-parameters";
inline constexpr char kMaxStaticIfStatements[] = "max-static-if-statements";
inline constexpr char kMaxStaticWhileStatements[] = "max-static-while-statements";
inline constexpr char kMaxStaticVariableDeclarations[] = "max-static-variable-declarations";
inline constexpr char kMaxStaticAssignments[] = "max-static-assignments";
inline constexpr char kMaxStaticReturnStatements[] = "max-static-return-statements";
inline constexpr char kMaxStaticFunctionCalls[] = "max-static-function-calls";
inline constexpr char kMaxStaticBinaryExpressions[] = "max-static-binary-expressions";
inline constexpr char kMaxStaticUnaryExpressions[] = "max-static-unary-expressions";
inline constexpr char kMaxStaticIntLiterals[] = "max-static-int-literals";
inline constexpr char kMaxStaticBlockStatements[] = "max-static-block-statements";

inline constexpr char kMaxRuntimeExecutedIf[] = "max-runtime-executed-if";
inline constexpr char kMaxRuntimeExecutedWhileIterations[] = "max-runtime-executed-while-iterations";
inline constexpr char kMaxRuntimeExecutedFunctionCalls[] = "max-runtime-executed-function-calls";
inline constexpr char kMaxRuntimeExecutedAssignments[] = "max-runtime-executed-assignments";
inline constexpr char kMaxRuntimeExecutedVariableDeclarations[] =
    "max-runtime-executed-variable-declarations";
inline constexpr char kMaxRuntimeAdditions[] = "max-runtime-additions";
inline constexpr char kMaxRuntimeSubtractions[] = "max-runtime-subtractions";
inline constexpr char kMaxRuntimeMultiplications[] = "max-runtime-multiplications";
inline constexpr char kMaxRuntimeDivisions[] = "max-runtime-divisions";
inline constexpr char kMaxRuntimeComparisons[] = "max-runtime-comparisons";
inline constexpr char kMaxRuntimeUnaryNegations[] = "max-runtime-unary-negations";
inline constexpr char kMaxRuntimeReturns[] = "max-runtime-returns";
inline constexpr char kMaxRuntimePrintCalls[] = "max-runtime-print-calls";
inline constexpr char kMaxRuntimeInputCalls[] = "max-runtime-input-calls";

struct SupportedLimitOption {
    std::string_view cli_flag;
    std::string_view limit_key;
    std::string_view description;
};

inline constexpr std::array<SupportedLimitOption, 26> kSupportedLimitOptions{
    {{"--max-static-functions", kMaxStaticFunctions, "Maximum number of functions in AST."},
        {"--max-static-parameters", kMaxStaticParameters,
            "Maximum number of function parameters in AST."},
        {"--max-static-if-statements", kMaxStaticIfStatements,
            "Maximum number of if/if-else statements in AST."},
        {"--max-static-while-statements", kMaxStaticWhileStatements,
            "Maximum number of while statements in AST."},
        {"--max-static-variable-declarations", kMaxStaticVariableDeclarations,
            "Maximum number of variable declarations in AST."},
        {"--max-static-assignments", kMaxStaticAssignments, "Maximum number of assignments in AST."},
        {"--max-static-return-statements", kMaxStaticReturnStatements,
            "Maximum number of return statements in AST."},
        {"--max-static-function-calls", kMaxStaticFunctionCalls,
            "Maximum number of function call expressions in AST."},
        {"--max-static-binary-expressions", kMaxStaticBinaryExpressions,
            "Maximum number of binary expressions in AST."},
        {"--max-static-unary-expressions", kMaxStaticUnaryExpressions,
            "Maximum number of unary expressions in AST."},
        {"--max-static-int-literals", kMaxStaticIntLiterals,
            "Maximum number of int literals in AST."},
        {"--max-static-block-statements", kMaxStaticBlockStatements,
            "Maximum number of block statements in AST."},
        {"--max-runtime-executed-if", kMaxRuntimeExecutedIf,
            "Maximum number of executed if/if-else checks."},
        {"--max-runtime-executed-while-iterations", kMaxRuntimeExecutedWhileIterations,
            "Maximum number of executed while iterations."},
        {"--max-runtime-executed-function-calls", kMaxRuntimeExecutedFunctionCalls,
            "Maximum number of executed function calls."},
        {"--max-runtime-executed-assignments", kMaxRuntimeExecutedAssignments,
            "Maximum number of executed assignments."},
        {"--max-runtime-executed-variable-declarations",
            kMaxRuntimeExecutedVariableDeclarations,
            "Maximum number of executed variable declarations."},
        {"--max-runtime-additions", kMaxRuntimeAdditions, "Maximum number of executed additions."},
        {"--max-runtime-subtractions", kMaxRuntimeSubtractions,
            "Maximum number of executed subtractions."},
        {"--max-runtime-multiplications", kMaxRuntimeMultiplications,
            "Maximum number of executed multiplications."},
        {"--max-runtime-divisions", kMaxRuntimeDivisions, "Maximum number of executed divisions."},
        {"--max-runtime-comparisons", kMaxRuntimeComparisons,
            "Maximum number of executed comparisons."},
        {"--max-runtime-unary-negations", kMaxRuntimeUnaryNegations,
            "Maximum number of executed unary negations."},
        {"--max-runtime-returns", kMaxRuntimeReturns, "Maximum number of executed returns."},
        {"--max-runtime-print-calls", kMaxRuntimePrintCalls,
            "Maximum number of executed print calls."},
        {"--max-runtime-input-calls", kMaxRuntimeInputCalls,
            "Maximum number of executed input calls."}}};

inline std::optional<std::string> FindLimitKeyByCliFlag(std::string_view cli_flag) {
    for (const auto& option : kSupportedLimitOptions) {
        if (option.cli_flag == cli_flag) {
            return std::string(option.limit_key);
        }
    }
    return std::nullopt;
}

inline bool CheckLimit(
    const LimitsMap& limits, const std::string& key, std::int64_t actual, std::string* out_error) {
    auto limit_value = limits.Get(key);
    if (!limit_value.has_value()) {
        return true;
    }

    if (actual <= *limit_value) {
        return true;
    }

    if (out_error != nullptr) {
        *out_error = ::utils::FormatStream() << "Limit \"" << key << "\" exceeded: actual "
                                             << actual << ", limit " << *limit_value << ".";
    }
    return false;
}

}  // namespace lang::limits
