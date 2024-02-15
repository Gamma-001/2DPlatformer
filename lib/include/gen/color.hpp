#pragma once

#include <type_traits>
#include <cstdint>
#include <array>
#include <algorithm>

template <class T, int TChannel>
class Color {
    static_assert((std::is_integral_v<T> || std::is_floating_point_v<T>) && TChannel >= 1 && TChannel <= 4);

public:
    Color();
    template <typename... Targs>
    Color(Targs... _args);

    inline T& r() { return mData[0]; }
    template <bool hasGreen = (TChannel >= 2), typename = typename std::enable_if_t<hasGreen && (hasGreen == (TChannel >= 2))>>
    inline T& g() { return mData[1]; }
    template <bool hasBlue = (TChannel >= 3), typename = typename std::enable_if_t<hasBlue && (hasBlue == (TChannel >= 3))>>
    inline T& b() { return mData[2]; }
    template <bool hasAlpha = (TChannel >= 4), typename = typename std::enable_if_t<hasAlpha && (hasAlpha == (TChannel >= 4))>>
    inline T& a() { return mData[3]; }

    inline T getIndex(int i) const { return mData[i]; }
    inline void setIndex(int i, T _val) {
        if (i >= 0 && i < TChannel) mData[i] = _val; 
    }

private:
    std::array <T, TChannel> mData;
};

template <class T, int TChannel>
Color<T, TChannel>::Color() {
    std::fill(mData.begin(), mData.end(), static_cast<T>(0));
}

template <class T, int TChannel>
template <typename... Targs>
Color<T, TChannel>::Color(Targs... _args) {
    static_assert(sizeof...(Targs) == TChannel);

    mData = std::array <T, TChannel> { _args... };
}

typedef Color<float, 4>     Color_FRGBA;
typedef Color<float, 3>     Color_FRGB;
typedef Color<uint8_t, 4>   Color_URGBA;
typedef Color<uint8_t, 3>   Color_URGB;