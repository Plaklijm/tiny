#pragma once
#include <compare>
#include <cstddef>
#include <type_traits>
#include <format>
#include <string>
#include <ostream>
#include "setup.hpp"

namespace tiny::math
{
    template <arithmetic T>
    struct vec<2, T>
    {
        T x{}, y{};
     
        constexpr vec() = default;
        constexpr vec(const vec& v) = default;
        constexpr explicit vec(T scalar) : x(scalar), y(scalar) {};
        constexpr vec(T x, T y) : x(x), y(y) {};
        template <typename X, typename Y>
        constexpr vec(X x, Y y) : x(static_cast<T>(x)), y(static_cast<T>(y)) {};
        
        constexpr T& operator [](const length_t i) {
            switch (i)
            {
                default:
                case 0: return x;
                case 1: return y;
            };
        }
        constexpr const T&  operator [](const length_t i) const {
            switch (i)
            {
            default:
            case 0: return x;
            case 1: return y;
            };
        }
        // gives operator == and !=
        constexpr bool operator==(const vec&) const = default;
        // Spaceship operator, includes all the default operators: <, <=, >, >=
        // Use for sorting or containers, vec < vec isn't correct algebra
        constexpr auto operator<=>(const vec&) const = default;
    };
    
    template <arithmetic T>
    struct vec<3, T>
    {
        T x{}, y{}, z{};
        
        constexpr vec() = default;
        constexpr vec(const vec& v) = default;
        constexpr explicit vec(T scalar) : x(scalar), y(scalar), z(scalar) {}; 
        constexpr vec(T x, T y, T z) : x(x), y(y), z(z) {};
        template <typename X, typename Y, typename Z>
        constexpr vec(X x, Y y, Z z) : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z)) {};
        
        constexpr T& operator [](const length_t i) {
            switch (i)
            {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            };
        }
        constexpr const T& operator [](const length_t i) const {
            switch (i)
            {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            };
        }
        // gives operator == and !=
        constexpr bool operator==(const vec&) const = default;
        // Spaceship operator, includes all the default operators: <, <=, >, >=
        // Use for sorting or containers, vec < vec isn't correct algebra
        constexpr auto operator<=>(const vec&) const = default;
    };
    
    
    template <arithmetic T>
    struct vec<4, T>
    {
        T x{}, y{}, z{}, w{};
        
        constexpr vec() = default;
        constexpr vec(const vec& v) = default;
        constexpr explicit vec(T scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {};
        constexpr vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};
        template <typename X, typename Y, typename Z, typename W>
        constexpr vec(X x, Y y, Z z, W w) : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z)), w(static_cast<T>(w)) {};
        
        constexpr T& operator [](const length_t i) {
            switch (i)
            {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            };
        }
        constexpr const T& operator [](const length_t i) const {
            switch (i)
            {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            };
        }
        // gives operator == and !=
        constexpr bool operator==(const vec&) const = default;
        // Spaceship operator, includes all the default operators: <, <=, >, >=
        // Use for sorting or containers, vec < vec isn't correct algebra
        constexpr auto operator<=>(const vec&) const = default;
    };
    
    template <length_t L, arithmetic T>
    constexpr vec<L, T>& operator+=(vec<L, T>& a, const vec<L, T>& b) { for (length_t i = 0; i < L; ++i) a[i] += b[i]; return a; }
    template <length_t L, arithmetic T>
    constexpr vec<L, T>& operator-=(vec<L, T>& a, const vec<L, T>& b) { for (length_t i = 0; i < L; ++i) a[i] -= b[i]; return a; }
    template <length_t L, arithmetic T>
    constexpr vec<L, T>& operator*=(vec<L, T>& v, const std::type_identity_t<T> s) { for (length_t i = 0; i < L; ++i) v[i] *= s; return v; }
    template <length_t L, arithmetic T>
    constexpr vec<L, T>& operator/=(vec<L, T>& v, const std::type_identity_t<T> s) { for (length_t i = 0; i < L; ++i) v[i] /= s; return v; }
    
    template <length_t L, arithmetic T>
    constexpr vec<L, T> operator+(vec<L, T> a, const vec<L, T>& b) { return a += b; }
    template <length_t L, arithmetic T>
    constexpr vec<L, T> operator-(vec<L, T> a, const vec<L, T>& b) { return a -= b; }
    template <length_t L, arithmetic T>
    constexpr vec<L, T> operator-(vec<L, T> v) { for (length_t i = 0; i < L; ++i) v[i] = -v[i]; return v; } // negate vector
    template <length_t L, arithmetic T>
    constexpr vec<L, T> operator*(vec<L, T> v, const std::type_identity_t<T> s)    { return v *= s; }
    template <length_t L, arithmetic T>
    constexpr vec<L, T> operator*(const std::type_identity_t<T> s, vec<L, T> v)    { return v *= s; }
    template <length_t L, arithmetic T>
    constexpr vec<L, T> operator/(vec<L, T> v, const std::type_identity_t<T> s)    { return v /= s; }
    
    template <length_t L, arithmetic T>
    std::string to_string(const vec<L, T>& v)
    {
        std::string result = "(";
        for (length_t i = 0; i < L; ++i)
        {
            if (i > 0) { result += ", "; } 
            result += std::format("{:.2f}", v[i], 2);
        }
        result += ")";
        return result;
    }
    
    template <length_t L, arithmetic T>
    std::ostream& operator<<(std::ostream& os, const vec<L, T>& v) { return os << to_string(v); }
}
