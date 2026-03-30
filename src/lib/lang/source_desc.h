#pragma once

#include <cstddef>

namespace lib::lang::engines {
class Sources;
}

namespace lib::lang {

class SourceDesc {
    friend class engines::Sources;

private:
    explicit SourceDesc(size_t source_id) : source_id_(source_id) {}

public:
    size_t GetSourceId() const {
        return source_id_;
    }

    bool operator==(SourceDesc another) const {
        return GetSourceId() == another.GetSourceId();
    }

private:
    size_t source_id_;
};

}  // namespace lib::lang
