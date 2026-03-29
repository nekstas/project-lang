#pragma once

#include <any>
#include <string>
#include <typeindex>

namespace lib::flow {

template <typename Context>
class Stage {
public:
    virtual ~Stage() {}

    virtual std::any RunAny(std::any input, Context& ctx) const = 0;
    virtual std::type_index InputType() const = 0;
    virtual std::type_index OutputType() const = 0;

    virtual std::string Name() const = 0;
};

}  // namespace lib::flow
