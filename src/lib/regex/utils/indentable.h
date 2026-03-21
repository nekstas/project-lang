#pragma once

#include <cstdint>
#include <string>

namespace lang::regex::utils {

class Indentable;

class WithIndent {
public:
    WithIndent(Indentable& ast_printer);
    ~WithIndent();
    WithIndent(const WithIndent&) = delete;
    WithIndent(WithIndent&&) = delete;
    WithIndent& operator=(const WithIndent&) = delete;
    WithIndent& operator=(WithIndent&&) = delete;

private:
    Indentable& ast_printer_;
};

class LinePrinter {
public:
    friend class Indentable;

private:
    LinePrinter(const std::string& indent, bool use_newlines, std::ostream& out);

public:
    ~LinePrinter();

    template <typename T>
    LinePrinter& operator<<(const T& object) {
        out_ << object;
        return *this;
    }

private:
    bool use_newlines_;
    std::ostream& out_;
};

class Indentable {
public:
    friend class utils::WithIndent;

public:
    explicit Indentable(size_t indent_spaces, bool use_newlines = true);
    explicit Indentable(const std::string& indent_step, bool use_newlines = true);

    LinePrinter Line(std::ostream& out);

private:
    void AddIndent();
    void RemoveIndent();

private:
    std::string indent_{};
    std::string indent_step_;
    bool use_newlines_;
};

}  // namespace lang::regex::utils
