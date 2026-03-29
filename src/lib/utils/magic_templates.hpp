#pragma once

namespace utils {  // TypeTag

template <typename T>
struct TypeTag {
    using Type = T;
};

}  // namespace utils

namespace utils {  // Overloaded

template <class... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

}  // namespace utils

namespace utils {  // RunTraits

template <typename T>
struct RunTraits;

template <typename R, typename In, typename Ctx>
struct RunTraits<R (*)(In, Ctx&)> {
    using InputType = In;
    using OutputType = R;
};

template <typename R, typename In, typename Ctx>
struct RunTraits<R(In, Ctx&)> {
    using InputType = In;
    using OutputType = R;
};

template <typename C, typename R, typename In, typename Ctx>
struct RunTraits<R (C::*)(In, Ctx&)> {
    using InputType = In;
    using OutputType = R;
};

template <typename C, typename R, typename In, typename Ctx>
struct RunTraits<R (C::*)(In, Ctx&) const> {
    using InputType = In;
    using OutputType = R;
};

}  // namespace utils
