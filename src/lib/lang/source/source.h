#pragma once

#include <string>
#include <vector>

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

    size_t Size() const {
        return GetContent().size();
    }

private:
    void BuildIndex();

private:
    std::string name_;
    std::string content_;
    std::vector<size_t> line_starts_;
};

std::ostream& operator<<(std::ostream& out, const Source& file);

template <typename T>
concept DerivedSource = std::derived_from<T, Source>;

}  // namespace lib::lang::source
