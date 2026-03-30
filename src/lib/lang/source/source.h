#pragma once

#include <string>

#include "index.h"
#include "line_column.h"

namespace lib::lang::source {

class Source {
public:
    Source(const std::string& name, const std::string& content);

    virtual ~Source() {}

    virtual std::string GetTitle() const = 0;

    const std::string& GetName() const {
        return name_;
    }

    const std::string& GetContent() const {
        return content_;
    }

    std::string GetLine(size_t line_number) const;

    const Index& GetIndex() const {
        return index_;
    }

    size_t Size() const {
        return index_.Size();
    }

private:
    std::string name_;
    std::string content_;
    Index index_;
};

std::ostream& operator<<(std::ostream& out, const Source& source);

template <typename T>
concept DerivedSource = std::derived_from<T, Source>;

}  // namespace lib::lang::source
