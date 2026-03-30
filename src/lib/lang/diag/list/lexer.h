#pragma once

#include "../../source/span.h"

namespace lib::lang::diag {

// TODO: Поменять имя на более общее, чтобы и для парсера и остального подходило
class LexerDiag : public Diag {
public:
    LexerDiag(Severity severity, const source::Span& span) : Diag(severity), span_(span) {}

    virtual std::string GetSubMessage() const = 0;

    std::string GetMessage(const RenderContext& ctx) const override {
        ::utils::FormatStream out;
        const auto& source = ctx.src.GetSource(span_.GetDesc());
        // TODO: TEMP
        out << source.GetName();
        out << " at offset = " << span_.GetOffset();
        out << ", length = " << span_.GetLength() << "\n";
        out << source;
        return out;
    }

protected:
    source::Span GetSpan() const {
        return span_;
    }

private:
    source::Span span_;
};

class UnexpectedSymbolError : public LexerDiag {
public:
    explicit UnexpectedSymbolError(const source::Span& span) : LexerDiag(Severity::ERROR, span) {}

    std::string GetSubMessage() const override {
        return "Unexpected symbol.";
    }
};

// class FileFatal : public FileDiag {
// public:
//     explicit FileFatal(const source::Path& path) : FileDiag(Severity::FATAL, path) {}
// };
//
// class CannotOpenFileFatal : public FileFatal {
// public:
//     explicit CannotOpenFileFatal(const source::Path& path) : FileFatal(path) {}
//
//     std::string GetMessage() const override {
//         return ::utils::FormatStream{} << "Cannot open file " << GetPath() << ".";
//     }
// };
//
// class FileIOFatal : public FileFatal {
// public:
//     explicit FileIOFatal(const source::Path& path) : FileFatal(path) {}
//
//     std::string GetMessage() const override {
//         return ::utils::FormatStream{} << "I/O error while reading file " << GetPath() << ".";
//     }
// };

}  // namespace lib::lang::diag
