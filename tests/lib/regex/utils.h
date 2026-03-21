#pragma once

#include <vector>

#include "../../../src/lib/regex/ast/all.h"
#include "../../../src/lib/regex/parser/parser.h"
#include "../../../src/lib/regex/visitors/ast_printer.h"

using lang::regex::ast::CharNode;
using lang::regex::ast::Node;

class AstBuilder {
private:
    using NodesVector = std::vector<std::unique_ptr<Node>>;

public:
    AstBuilder& AddNode(std::unique_ptr<Node> node) {
        nodes_.emplace_back(std::move(node));
        return *this;
    }

    template <typename T, typename... Args>
    AstBuilder& Add(Args&&... args) {
        return AddNode(std::make_unique<T>(std::forward<Args>(args)...));
    }

    AstBuilder& AddChar(uint8_t code) {
        return Add<CharNode>(code);
    }

    AstBuilder& AddChars(const std::string& str) {
        for (const auto code : str) {
            AddChar(code);
        }
        return *this;
    }

    template <typename T>
    std::unique_ptr<T> Make() {
        auto result = std::make_unique<T>(std::move(nodes_));
        nodes_ = NodesVector{};
        return std::move(result);
    }

private:
    NodesVector nodes_;
};
