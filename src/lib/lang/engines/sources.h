#pragma once

#include <memory>

#include "../../errors/errors.h"
#include "../source/source.h"
#include "../source_desc.h"
#include "../stats/src/analyzer.h"

namespace lib::lang::engines {

class Sources {
public:
    template <source::DerivedSource SourceType, typename... Args>
    SourceDesc AddSource(Args&&... args) {
        SourceDesc desc = AddSource(std::make_unique<SourceType>(std::forward<Args>(args)...));
        const auto& source = GetSource(desc);
        stats_.AddSource(source);
        return desc;
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

    const stats::src::Stats& GetStats() const {
        return stats_.GetStats();
    }

private:
    SourceDesc AddSource(std::unique_ptr<source::Source> source) {
        size_t source_id = sources_.size();
        sources_.emplace_back(std::move(source));
        return SourceDesc{source_id};
    }

private:
    std::vector<std::unique_ptr<source::Source>> sources_;
    stats::src::Analyzer stats_;
};

}  // namespace lib::lang::engines
