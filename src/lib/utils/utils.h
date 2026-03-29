#pragma once

#include <cstdint>
#include <queue>
#include <string_view>

namespace utils {

bool IsIn(uint8_t ch, std::string_view symbols);

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

template <class... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

}  // namespace utils
