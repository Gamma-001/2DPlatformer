#pragma once

#include <type_traits>

namespace detail {
    template <class T> 
    class Color3Ref {
    public:
        inline Color3Ref(T _r = 0, T _g = 0, T _b = 0): r(_r), g(_g), b(_b) {}

        T r, g, b;
    };

    template <class T>
    class Color4Ref {
    public:
        inline Color4Ref(T _r = 0, T _g = 0, T _b = 0, T _a = 0): r(_r), g(_g), b(_b), a(_a) {}

        T r, g, b, a;
    };
}

template <class T, bool useAlpha = true>
class Color: public std::conditional_t<useAlpha, detail::Color4Ref<T>, detail::Color3Ref<T>> {
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "T must be an integral or floating type");

public:
    template <bool enable = useAlpha, typename = typename std::enable_if_t<enable && useAlpha>>
    Color(T _r = 0, T _g = 0, T _b = 0, T _a = 0);

    template <bool enable = !useAlpha, typename = typename std::enable_if_t<enable && !useAlpha>>
    Color(T _r = 0, T _g = 0, T _b = 0);

    using ColorRef = std::conditional<useAlpha, detail::Color4Ref<T>, detail::Color3Ref<T>>::type;
};

template <class T, bool useAlpha>
template <bool enable, typename>
Color<T, useAlpha>::Color(T _r, T _g, T _b, T _a)
:ColorRef(_r, _g, _b, _a) {}

template <class T, bool useAlpha>
template <bool enable, typename>
Color<T, useAlpha>::Color(T _r, T _g, T _b)
:ColorRef(_r, _g, _b) {}