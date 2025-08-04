#pragma once
#include "../Math/Vector2.h"
#include "../Math/Math.h"
#include <cstdlib>
#include <random>

namespace viper::random {
    inline std::mt19937& generator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    inline void seed(unsigned int value) {
        generator().seed(value);
    }

    inline int getInt(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);
        return dist(generator());
    }

    inline int getInt(int max) {
        return getInt(0, max - 1);
    }

    inline int getInt() {
        static std::uniform_int_distribution<> dist;
        return dist(generator());
    }

    /// <summary>
    /// Generates a random real number within the specified range [min, max).
    /// </summary>
    /// <typeparam name="T">The floating-point type to use for the random number (defaults to float).</typeparam>
    /// <param name="min">The lower bound of the range (inclusive).</param>
    /// <param name="max">The upper bound of the range (exclusive).</param>
    /// <returns>A random real number of type T in the range [min, max).</returns>
    template <typename T = float>
    inline T getReal(T min, T max) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(generator());
    }

    /// <summary>
    /// Generates a random real number in the range [0, max).
    /// </summary>
    /// <typeparam name="T">The floating-point type to use for the random number (defaults to float).</typeparam>
    /// <param name="max">The exclusive upper bound for the generated random number.</param>
    /// <returns>A random real number of type T in the range [0, max).</returns>
    template <typename T = float>
    inline T getReal(T max) {
        return getReal(static_cast<T>(0), static_cast<T>(max));
    }

    /// <summary>
    /// Generates a random real number in the range [0, 1).
    /// </summary>
    /// <typeparam name="T">The floating-point type of the generated number. Defaults to float.</typeparam>
    /// <returns>A random real number of type T in the range [0, 1).</returns>
    template <typename T = float>
    inline T getReal() {
        static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
        return dist(generator());
    }

    inline bool getBool() {
        static std::bernoulli_distribution dist(0.5);
        return dist(generator());
    }

    inline vec2 onUnitCircle() {
		float radians = getReal(math::twoPi);
        vec2 v;
		v.x = math::cosf(radians);
        v.y = math::sinf(radians);
		return v;
    }
}