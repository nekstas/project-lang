#pragma once

#include <memory>
#include <vector>

namespace lib::lang::asm_ {

template <typename AsmLine>
class Unit {
public:
    template <typename LineType, typename... Args>
    void AddLine(Args&&... args) {
        AddLine(std::make_unique<LineType>(std::forward<Args>(args)...));
    }

    void AddLine(std::unique_ptr<AsmLine> line) {
        lines_.emplace_back(std::move(line));
    }

    template <typename LineType, typename... Args>
    void InsertLine(size_t index, Args&&... args) {
        InsertLine(index, std::make_unique<LineType>(std::forward<Args>(args)...));
    }

    void InsertLine(size_t index, std::unique_ptr<AsmLine> line) {
        lines_.emplace(index, std::move(line));
    }

    size_t Size() const {
        return lines_.size();
    }

    const std::vector<std::unique_ptr<AsmLine>>& GetLines() const {
        return lines_;
    }

private:
    std::vector<std::unique_ptr<AsmLine>> lines_;
};

}  // namespace lib::lang::asm_
