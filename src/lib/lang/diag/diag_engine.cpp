#include "diag_engine.h"

#include <sstream>

namespace lib::lang::diag {

std::string DiagEngine::GetDiagnosticsString() const {
    if (Empty()) {
        return "No diagnostics found.\n";
    }
    std::stringstream out;
    out << GetDiagnosticsCount() << " diagnostics found.\n";
    for (const auto& diag : diags_) {
        out << diag->GetMessage() << "\n";
    }
    return out.str();
}

bool DiagEngine::Empty() const {
    return GetDiagnosticsCount() == 0;
}

size_t DiagEngine::GetDiagnosticsCount() const {
    return diags_.size();
}

size_t DiagEngine::GetSeverityCount(Severity severity) const {
    if (counts_.contains(severity)) {
        return counts_.at(severity);
    }
    return 0;
}

size_t DiagEngine::GetErrorsCount() const {
    return GetSeverityCount(Severity::ERROR);
}

bool DiagEngine::HasFatal() const {
    return GetSeverityCount(Severity::FATAL) > 0;
}

bool DiagEngine::ShouldStop() const {
    return HasFatal() || GetErrorsCount() >= max_error_count_;
}

void DiagEngine::AddSeverityCount(Severity severity) {
    ++counts_[severity];
}

}  // namespace lib::lang::diag
