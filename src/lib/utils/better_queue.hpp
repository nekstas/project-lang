#pragma once

#include <queue>

namespace utils {

template <typename T>
class BetterQueue : public std::queue<T> {
public:
    using std::queue<T>::queue;

    T Extract() {
        T result = std::queue<T>::front();
        std::queue<T>::pop();
        return result;
    }
};

}  // namespace utils
