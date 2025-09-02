#pragma once
namespace viper {

    template<typename T>
    struct Rect {
        T x, y, w, h;

        Rect() : x(0), y(0), w(0), h(0) {}
        Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
    };

    using rect = Rect<float>;
    using irect = Rect<int>;

}