#pragma once

#include <memory>

#include "../../errors/errors.h"
#include "../source/source.h"
#include "../source_desc.h"

namespace lib::lang::engines {

class Sources {
public:
    template <source::DerivedSource SourceType, typename... Args>
    SourceDesc AddSource(Args&&... args) {
        return AddSource(std::make_unique<SourceType>(std::forward<Args>(args)...));
    }

    const source::Source& GetSource(SourceDesc desc) const {
        THROW_IF(desc.GetSourceId() >= Size(), ::errors::LogicError,
            "Unknown source with id = " << desc.GetSourceId() << " while there are only " << Size()
                                        << "sources.");
        return *sources_[desc.GetSourceId()];
    }

    size_t Size() const {
        return sources_.size();
    }

private:
    SourceDesc AddSource(std::unique_ptr<source::Source> source) {
        size_t source_id = sources_.size();
        sources_.emplace_back(std::move(source));
        return SourceDesc{source_id};
    }

private:
    std::vector<std::unique_ptr<source::Source>> sources_;
};

}  // namespace lib::lang::engines
