#pragma once
#include <cstddef>
#include <type_traits>

namespace tiny::math
{
    // C++20 concept, to make sure a vector can only be occupied by arithmetic types
    template <typename T>
    concept arithmetic = std::is_arithmetic_v<T>;

    template <typename T>
    concept floating_point = std::is_floating_point_v<T>;

    using length_t = std::size_t;

    // Enforce support for vec 2, 3, 4
    template <length_t L, arithmetic T>
        requires (L >= 2 && L <= 4)
    struct vec;
    
    // Enforce support for every type of matrix, ranging from 2 to 4
    template <length_t C, length_t R, arithmetic T>
        requires ((C >= 2 && C <= 4) && (R >= 2 && R <= 4))
    struct mat;
    
    // Quaternion is always a fixed size
    template <arithmetic T>
    struct quat;


    template <length_t L, arithmetic R, arithmetic T>
    struct functor_single_vec
    {
        constexpr static vec<L, R> call(R (*Func)(T x), const vec<L, T>& v)
        {
            vec<L, R> result{};
            for (length_t i = 0; i < L; ++i)
            {
                result[i] = Func(v[i]);
            }

            return result;
        }
    };

    template <length_t L, arithmetic R, arithmetic T>
    struct functor_double_vec
    {
        constexpr static vec<L, R> call(R (*Func)(T x, T y), const vec<L, T>& a, const vec<L, T>& b)
        {
            vec<L, R> result{};
            for (length_t i = 0; i < L; ++i)
            {
                result[i] = Func(a[i], b[i]);
            }

            return result;
        }
    };

    template <length_t L, arithmetic R, arithmetic T>
    struct functor_vec_scalar
    {
        constexpr static vec<L, R> call(R (*Func)(T x, T y), const vec<L, T>& a, T b)
        {
            vec<L, R> result{};
            for (length_t i = 0; i < L; ++i)
            {
                result[i] = Func(a[i], b);
            }

            return result;
        }
    };
}
