#pragma once

#include <map>
#include <memory>
#include <vector>

#include "../../flow/stage.hpp"
#include "../../flow/stop_pipeline.hpp"
#include "diag.h"

namespace lib::lang::diag {

class DiagEngine {
public:
    explicit DiagEngine(size_t max_error_count) : max_error_count_(max_error_count) {}

    template <typename Context>
    void Report(const flow::Stage<Context>& stage, std::unique_ptr<Diag> diag) {
        diags_.emplace_back(std::move(diag));
        AddSeverityCount(diags_.back()->GetSeverity());
        StopIfShould(stage);
    }

    template <DerivedDiag DiagType, typename Context, typename... Args>
    void Report(const flow::Stage<Context>& stage, Args&&... args) {
        Report(stage, std::make_unique<DiagType>(std::forward<Args>(args)...));
    }

    std::string GetDiagnosticsString() const;

private:
    bool Empty() const;

    size_t GetDiagnosticsCount() const;

    size_t GetSeverityCount(Severity severity) const;

    size_t GetErrorsCount() const;

    bool HasFatal() const;

    bool ShouldStop() const;

    void AddSeverityCount(Severity severity);

    template <typename Context>
    void StopIfShould(const flow::Stage<Context>& stage) const {
        if (ShouldStop()) {
            throw flow::StopPipeline{stage.Name()};
        }
    }

private:
    size_t max_error_count_;
    std::map<Severity, size_t> counts_;
    std::vector<std::unique_ptr<Diag>> diags_;
};

}  // namespace lib::lang::diag
