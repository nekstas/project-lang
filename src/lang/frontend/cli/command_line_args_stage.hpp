#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "../../../lib/flow/typed_stage.hpp"
#include "../../../lib/lang/context/base_context.h"
#include "../../../lib/lang/macros.h"
#include "../../diag/list/constraints.h"
#include "../../limits/constraints.h"

namespace lang::frontend {

template <lib::lang::ContextLike Context>
class CommandLineArgsStage : public lib::flow::TypedStage<CommandLineArgsStage<Context>, Context,
                                 std::vector<std::string>, std::filesystem::path> {
public:
    std::filesystem::path Run(std::vector<std::string> args, Context& ctx) const {
        DIAG_REPORT_IF(args.empty(), ctx, lang::diag::CommandLineFatal,
            "Expected source file path. Usage: ./lang <source_file> [--limit value]...");

        std::filesystem::path source_path = args.front();
        size_t i = 1;
        while (i < args.size()) {
            const std::string& key = args[i];
            if (!key.starts_with("--")) {
                DIAG_REPORT(ctx, lang::diag::CommandLineFatal,
                    "Unexpected positional argument \"" + key + "\".");
            }
            DIAG_REPORT_IF(i + 1 >= args.size(), ctx, lang::diag::CommandLineFatal,
                "Expected value after \"" + key + "\".");

            const std::string& value_str = args[i + 1];
            auto limit_key = limits::FindLimitKeyByCliFlag(key);
            DIAG_REPORT_IF(!limit_key.has_value(), ctx, lang::diag::CommandLineFatal,
                "Unknown option \"" + key + "\".");

            std::int64_t value = 0;
            try {
                value = std::stoll(value_str);
            } catch (...) {
                DIAG_REPORT(ctx, lang::diag::CommandLineFatal,
                    "Invalid integer value \"" + value_str + "\" for option \"" + key + "\".");
            }
            DIAG_REPORT_IF(value < 0, ctx, lang::diag::CommandLineFatal,
                "Negative limit \"" + key + "\" is not allowed.");

            ctx.limits.Set(*limit_key, value);
            i += 2;
        }

        return source_path;
    }

    std::string Name() const override {
        return "CommandLineArgs";
    }
};

}  // namespace lang::frontend
