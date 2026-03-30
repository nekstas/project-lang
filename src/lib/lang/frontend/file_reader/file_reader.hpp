#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

#include "../../../flow/typed_stage.hpp"
#include "../../context/base_context.h"
#include "../../diag/list/all.h"
#include "../../macros.h"
#include "../../source/file.h"

namespace lib::lang::frontend {

template <ContextLike Context>
class FileReader
    : public flow::TypedStage<FileReader<Context>, Context, std::filesystem::path, SourceDesc> {
public:
    SourceDesc Run(const std::filesystem::path& path, Context& ctx) const {
        source::Path file_path(path);

        std::ifstream in_file(path, std::ios::binary);
        DIAG_REPORT_IF(!in_file.is_open(), ctx, diag::CannotOpenFileFatal, file_path);

        std::stringstream content_stream;

        content_stream << in_file.rdbuf();
        DIAG_REPORT_IF(in_file.bad(), ctx, diag::FileIOFatal, file_path);

        return ctx.src.template AddSource<source::File>(file_path, content_stream.str());
    }

    std::string Name() const override {
        return "ReadFile";
    }
};

}  // namespace lib::lang::frontend
