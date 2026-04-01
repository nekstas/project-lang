#pragma once

#include "../../utils/format_stream.h"
#include "source.h"

namespace lib::lang::source {

class Program : public Source {
public:
    Program(const std::string& name, const std::string& content);

    explicit Program(const std::string& content) : Program("<program>", content) {}

    std::string GetTitle() const override;
};

}  // namespace lib::lang::source
