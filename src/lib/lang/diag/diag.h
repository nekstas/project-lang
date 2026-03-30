#pragma once

#include <concepts>
#include <string>

#include "../render/context.h"

namespace lib::lang::diag {

enum class Severity { NOTE, WARNING, ERROR, FATAL };

class Diag {
public:
    virtual ~Diag() {}

    explicit Diag(Severity severity);

    Severity GetSeverity() const {
        return severity_;
    }

    virtual std::string GetMessage(const render::Context& ctx) const = 0;

private:
    Severity severity_;
};

template <typename T>
concept DerivedDiag = std::derived_from<T, Diag>;

}  // namespace lib::lang::diag
