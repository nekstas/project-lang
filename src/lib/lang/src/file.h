#pragma once

#include "../../utils/format_stream.h"
#include "path.h"
#include "source.h"

namespace lib::lang::src {

class File : public Source {
public:
    File(const Path& path, const std::string& content);

    const Path& GetPath() const {
        return path_;
    }

    std::string GetTitle() const override;

protected:
    Path path_;
};

std::ostream& operator<<(std::ostream& out, const File& file);

}  // namespace lib::lang::src
