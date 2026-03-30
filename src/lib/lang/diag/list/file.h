#pragma once

#include "../../../utils/format_stream.h"
#include "../../source/path.h"
#include "../diag.h"

namespace lib::lang::diag {

class FileDiag : public Diag {
public:
    explicit FileDiag(Severity severity, const source::Path& path) : Diag(severity), path_(path) {}

protected:
    source::Path GetPath() const {
        return path_;
    }

private:
    source::Path path_;
};

class FileFatal : public FileDiag {
public:
    explicit FileFatal(const source::Path& path) : FileDiag(Severity::FATAL, path) {}
};

class CannotOpenFileFatal : public FileFatal {
public:
    explicit CannotOpenFileFatal(const source::Path& path) : FileFatal(path) {}

    std::string GetMessage(const RenderContext&) const override {
        return ::utils::FormatStream{} << "Cannot open file " << GetPath() << ".";
    }
};

class FileIOFatal : public FileFatal {
public:
    explicit FileIOFatal(const source::Path& path) : FileFatal(path) {}

    std::string GetMessage(const RenderContext&) const override {
        return ::utils::FormatStream{} << "I/O error while reading file " << GetPath() << ".";
    }
};

}  // namespace lib::lang::diag