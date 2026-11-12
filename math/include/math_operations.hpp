#pragma once

#include <cmath>
#include <concepts>
#include <limits>
#include <type_traits>

#include "setup.hpp"
#include "vec.hpp"

namespace tiny::math
{
    template <floating_point T>
    bool nearly_equal(T a, T b, std::type_identity_t<T> epsilon)
    {
        return abs(a - b) <= epsilon;
    }

    template <length_t L, floating_point T>
    bool nearly_equal(const vec<L, T>& a, const vec<L, T>& b, std::type_identity_t<T> epsilon)
    {
        for (length_t i = 0; i < L; ++i)
        {
            if (!nearly_equal(a[i], b[i], epsilon))
                return false;
        }
        return true;
    }

    /**
     * @brief Calculate the dot product of two vectors
     * 
     * The dot product is calculated using:
     * \f[
     *     a \cdot b = \sum_{i=1}^{n} a_i b_i = \lVert a \rVert \lVert b \rVert \cos\theta
     * \f]
     * where \f$\theta\f$ is the angle between a and b. The sign tells you their relative direction:
     * - positive: they point the same way (\f$\theta < 90^\circ\f$)
     * - zero: they are perpendicular
     * - negative: they point opposite ways (\f$\theta > 90^\circ\f$)
     *
     * If both vectors are normalized, the result is exactly \f$\cos\theta\f$.
     * 
     * @param a The first vector
     * @param b The second vector
     * @return The dot product of a and b
     */
    template <length_t L, arithmetic T>
    constexpr T dot(const vec<L, T>& a, const vec<L, T>& b)
    {
        T result{};
        for (length_t i = 0; i < L; ++i)
        {
            result += a[i] * b[i];
        }
        return result;
    }

    /**
     * @brief Calculate the squared magnitude (length) of a vector
     * 
     * The magnitude is calculated using:
     * \f[
     *     ||v||^2 = v_1^2 + v_2^2 + \cdots + v_n^2
     * \f]
     * @param v The vector
     * @return The squared magnitude of the vector
     */
    template <length_t L, arithmetic T>
    constexpr T length_squared(const vec<L, T>& v)
    {
        return dot(v, v);
    }

    /**
     * @brief Calculate the magnitude (length) of a vector
     * 
     * The magnitude is calculated using:
     * \f[
     *     ||v|| = \sqrt{v_1^2 + v_2^2 + \cdots + v_n^2}
     * \f]
     * @param v The vector
     * @return The magnitude of the vector
     */
    template <length_t L, floating_point T>
    T length(const vec<L, T>& v)
    {
        return std::sqrt(length_squared(v));
    }

    /**
     * @brief By normalizing we compute a unit vector that points in the same direction as a non-zero vector 
     * 
     * To normalize we:
     * \f[
     *     \hat{v} = \frac{v}{||v||}, \quad
     *     ||v|| = \sqrt{v_1^2 + v_2^2 + \cdots + v_n^2}
     * \f]
     * @note this needs to be a non-zero, floating point vector. A zero vector cannot be normalized because:
     * 1. Mathematically it would cause a division by zero
     * 2. Geometrically it does not define a direction
     * @param v Vector to normalize
     * @return A unit vector with the same direction as v
     */
    template <length_t L, floating_point T>
    vec<L, T> normalize(const vec<L, T>& v) { return v / length(v); }

    /**
     * @brief By normalizing we compute a unit vector that points in the same direction as a non-zero vector
     * It guards against zero vectors by returning a default constructed vector
     * 
     * To normalize we:
     * \f[
     *     \hat{v} = \frac{v}{||v||}, \quad
     *     ||v|| = \sqrt{v_1^2 + v_2^2 + \cdots + v_n^2}
     * \f]
     * @note If the length of v is too close to zero to normalize reliably, a zero vector is returned instead.
     * @param v Vector to safely normalize
     * @return A unit vector with the same direction as v, or a zero vector if v has (near-)zero length
     */
    template <length_t L, floating_point T>
    vec<L, T> safe_normalize(const vec<L, T>& v)
    {
        const auto l = length(v);
        if (l > std::numeric_limits<T>::epsilon())
        {
            return v / l;
        }

        // fallback to if the vector is 0, it constructs a default vec
        return vec<L, T>{};
    }

    /* 
     * @brief Normalizes the vector in place
     * @see vec<L, T> normalize(const vec<L, T>& v)
     * @param v Vector to normalize
     */
    template <length_t L, floating_point T>
    void normalize_in_place(vec<L, T>& v)
    {
        v = normalize(v);
    }

    /* 
     * @brief Safe normalizes the vector in place
     * @see vec<L, T> safe_normalize(const vec<L, T>& v)
     * @param v Vector to normalize
     */
    template <length_t L, floating_point T>
    void safe_normalize_in_place(vec<L, T>& v)
    {
        v = safe_normalize(v);
    }

    /**
     * @brief Calculate the squared distance between two points
     * 
     * The distance is calculated using 
     * \f[
     *     d(a, b)^2 = ||b - a||^2 = (b_1 - a_1)^2 + (b_2 - a_2)^2 + \cdots + (b_n - a_n)^2
     * \f]
     * Conceptually, you can think of the distance between 2 points as the length squared of the vector pointing from A to B
     * 
     * @param a The first point
     * @param b The second point
     * @return The squared distance between a and b
     */
    template <length_t L, arithmetic T>
    constexpr T distance_squared(const vec<L, T>& a, const vec<L, T>& b)
    {
        return length_squared(b - a);
    }

    /**
     * @brief Calculate the distance between two points
     * 
     * The distance is calculated using 
     * \f[
     *     d(a, b) = ||b - a|| = \sqrt{(b_1 - a_1)^2 + (b_2 - a_2)^2 + \cdots + (b_n - a_n)^2}
     * \f]
     * Conceptually, you can think of the distance between 2 points as the length of the vector pointing from A to B
     * @param a The first point
     * @param b The second point
     * @return The distance between a and b
     */
    template <length_t L, floating_point T>
    T distance(const vec<L, T>& a, const vec<L, T>& b)
    {
        return length(b - a);
    }

    /**
     * @brief
     * @param a 
     * @param b 
     * @return 
     */
    template <length_t L, floating_point T>
        requires (L == 3)
    constexpr vec<L, T> cross(const vec<L, T>& a, const vec<L, T>& b)
    {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

    /**
     * @brief
     * @param a 
     * @param b 
     * @return 
     */
    template <length_t L, floating_point T>
        requires (L == 4)
    constexpr vec<L, T> cross(const vec<L, T>& a, const vec<L, T>& b)
    {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x,
            T{}
        };
    }

    /**
     * @brief
     * @param a 
     * @param b 
     * @return 
     */
    template <length_t L, floating_point T>
        requires (L == 2)
    constexpr T cross_2d(const vec<L, T>& a, const vec<L, T>& b)
    {
        return a.x * b.y - a.y * b.x;
    }

    template <floating_point T>
    constexpr vec<2, T> perp(const vec<2, T>& v)
    {
        return {-v.y, v.x};
    }

    // cross
    // floor
    // ceil
    // clamp
    // round
    // min
    // max
    // abs
    // fmod
    // trunc
    // lerp
    // smoothstep
    // isnan
    // isinf
    // reflect
    // project
    // angle
    // perp
    // rotate
    // move_towards
    // radians/degree stuff
    // wrappers for things like acos, tan, atan2, sqrtm pow, exp, log etc
}
