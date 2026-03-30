#pragma once

#include <stack>

namespace utils {

template <typename T>
class BetterStack : public std::stack<T> {
private:
    using Super = std::stack<T>;

public:
    using std::stack<T>::stack;

    explicit BetterStack(std::initializer_list<T> values) {
        for (auto& value : values) {
            Super::push(value);
        }
    }

    T Extract() {
        T result = Super::top();
        Super::pop();
        return result;
    }

    void Clear() {
        while (!Super::empty()) {
            Super::pop();
        }
    }
};

}  // namespace utils
