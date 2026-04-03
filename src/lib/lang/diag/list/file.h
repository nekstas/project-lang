#pragma once

#include "../../errors/errors.h"
#include "../../render/line_highlight.h"
#include "../../src/path.h"
#include "../diag.h"

namespace lib::lang::diag {

class FileDiag : public Diag {
public:
    explicit FileDiag(Severity severity, const src::Path& path) : Diag(severity), path_(path) {}

protected:
    src::Path GetPath() const {
        return path_;
    }

private:
    src::Path path_;
};

class FileFatal : public FileDiag {
public:
    explicit FileFatal(const src::Path& path) : FileDiag(Severity::FATAL, path) {}

    virtual std::string GetSubMessage() const = 0;

    std::string GetMessage(const render::Context&) const override {
        std::stringstream out;
        out << GetPath().GetFullPath();
        out << ": " << GetSubMessage() << "\n";
        return out.str();
    }
};

class CannotOpenFileFatal : public FileFatal {
public:
    explicit CannotOpenFileFatal(const src::Path& path) : FileFatal(path) {}

    std::string GetSubMessage() const override {
        return "Cannot open file.";
    }
};

class FileIOFatal : public FileFatal {
public:
    explicit FileIOFatal(const src::Path& path) : FileFatal(path) {}

    std::string GetSubMessage() const override {
        return "I/O error while reading file.";
    }
};

class FileInvalidEncodingFatal : public FileFatal {
public:
    explicit FileInvalidEncodingFatal(
        const src::Path& path, const errors::InvalidEncodingInfo& err_info)
        : FileFatal(path), err_info_(err_info) {}

    std::string GetSubMessage() const override {
        std::stringstream out;
        out << "Invalid encoding at pos " << err_info_.length << ".\n";
        size_t align_length = utils::NumLength(err_info_.line_number);
        render::LineSpan line_span{err_info_.length, 2};
        out << render::LineHighlight(
            err_info_.prefix, err_info_.line_number, align_length, line_span);
        return out.str();
    }

private:
    errors::InvalidEncodingInfo err_info_;
};

}  // namespace lib::lang::diag