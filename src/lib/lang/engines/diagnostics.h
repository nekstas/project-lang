#pragma once

#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "../../flow/stage.hpp"
#include "../../flow/stop_pipeline.hpp"
#include "../diag/diag.h"

namespace lib::lang::engines {

class Diagnostics {
public:
    explicit Diagnostics(size_t max_error_count) : max_error_count_(max_error_count) {}

    template <diag::DerivedDiag DiagType, typename Context, typename... Args>
    void Report(const flow::Stage<Context>& stage, Args&&... args) {
        Report(stage, std::make_unique<DiagType>(std::forward<Args>(args)...));
    }

    template <typename Context>
    std::string GetDiagnosticsString(const Context& ctx) const {
        auto render_ctx = ConstructRenderContext(ctx);
        if (IsEmpty()) {
            return "No diagnostics found.\n";
        }
        std::stringstream out;
        out << GetDiagnosticsCount() << " diagnostics found.\n";
        for (const auto& diag : diags_) {
            out << diag->GetMessage(render_ctx) << "\n";
        }
        return out.str();
    }

private:
    template <typename Context>
    static diag::RenderContext ConstructRenderContext(const Context& common_ctx) {
        return diag::RenderContext{.src = common_ctx.src};
    }

    template <typename Context>
    void Report(const flow::Stage<Context>& stage, std::unique_ptr<diag::Diag> diag) {
        diags_.emplace_back(std::move(diag));
        AddSeverityCount(diags_.back()->GetSeverity());
        StopIfShould(stage);
    }

    bool IsEmpty() const;

    size_t GetDiagnosticsCount() const;

    size_t GetSeverityCount(diag::Severity severity) const;

    size_t GetErrorsCount() const;

    bool HasFatal() const;

    bool ShouldStop() const;

    void AddSeverityCount(diag::Severity severity);

    template <typename Context>
    void StopIfShould(const flow::Stage<Context>& stage) const {
        if (ShouldStop()) {
            throw flow::StopPipeline{stage.Name()};
        }
    }

private:
    size_t max_error_count_;
    std::unordered_map<diag::Severity, size_t> counts_;
    std::vector<std::unique_ptr<diag::Diag>> diags_;
};

}  // namespace lib::lang::engines
