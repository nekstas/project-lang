#include "diagnostics.h"

namespace lib::lang::engines {

bool Diagnostics::IsEmpty() const {
    return GetDiagnosticsCount() == 0;
}

size_t Diagnostics::GetDiagnosticsCount() const {
    return diags_.size();
}

size_t Diagnostics::GetSeverityCount(diag::Severity severity) const {
    if (counts_.contains(severity)) {
        return counts_.at(severity);
    }
    return 0;
}

size_t Diagnostics::GetErrorsCount() const {
    return GetSeverityCount(diag::Severity::ERROR);
}

bool Diagnostics::HasFatal() const {
    return GetSeverityCount(diag::Severity::FATAL) > 0;
}

bool Diagnostics::ShouldStop() const {
    return HasFatal() || GetErrorsCount() >= max_error_count_;
}

void Diagnostics::AddSeverityCount(diag::Severity severity) {
    ++counts_[severity];
}

}  // namespace lib::lang::engines
