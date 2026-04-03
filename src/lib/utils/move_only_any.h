#pragma once

#include <memory>
#include <type_traits>
#include <typeindex>
#include <utility>

#include "../errors/errors.h"

namespace utils {

class MoveOnlyAny {
private:
    class Block {
    public:
        virtual ~Block() {}

        virtual std::type_index Type() const {
            return typeid(void);
        }
    };

    template <typename T>
    class BlockWithValue : public Block {
    public:
        explicit BlockWithValue(T value) : value_(std::move(value)) {}

        T Take() {
            return std::move(value_);
        }

        std::type_index Type() const override {
            return typeid(T);
        }

    private:
        T value_;
    };

private:
    template <typename T>
    using TypedBlock = BlockWithValue<std::decay_t<T>>;

public:
    MoveOnlyAny() = default;

    ~MoveOnlyAny() {}

    template <typename T>
    // ReSharper disable once CppNonExplicitConvertingConstructor
    MoveOnlyAny(T&& value) {
        value_ = std::make_unique<TypedBlock<T>>(std::forward<T>(value));
    }

    template <typename T>
    MoveOnlyAny& operator=(T&& value) {
        MoveOnlyAny any(std::forward<T>(value));
        std::swap(*this, any);
        return *this;
    }

    MoveOnlyAny(MoveOnlyAny&& another) noexcept {
        std::swap(value_, another.value_);
    }

    MoveOnlyAny& operator=(MoveOnlyAny&& another) noexcept {
        std::swap(value_, another.value_);
        return *this;
    }

    MoveOnlyAny(const MoveOnlyAny&) = delete;
    MoveOnlyAny& operator=(const MoveOnlyAny&) = delete;

    template <typename T>
    std::decay_t<T> Take() {
        auto ptr = dynamic_cast<TypedBlock<T>*>(value_.get());
        THROW_IF(!ptr, ::errors::LogicError,
            "Can't extract this type of move-only-any (maybe another type or no value).");
        std::decay_t<T> real_value = ptr->Take();
        value_ = nullptr;
        return real_value;
    }

    std::type_index Type() const {
        return value_ ? value_->Type() : typeid(void);
    }

private:
    std::unique_ptr<Block> value_;
};

}  // namespace utils
