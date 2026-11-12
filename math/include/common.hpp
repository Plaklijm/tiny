#pragma once
#include "setup.hpp"

#include <cmath>

namespace tiny::math
{
    using ::std::abs;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> abs(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(abs, v); }
    
    using ::std::min;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> min(const vec<L, T>& a, const vec<L, T>& b) { return functor_double_vec<L, T, T>::call(min, a, b); }
    
    using ::std::max;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> max(const vec<L, T>& a, const vec<L, T>& b) { return functor_double_vec<L, T, T>::call(max, a, b); }
    
    using ::std::floor;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> floor(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(floor, v); }
    
    using ::std::ceil;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> ceil(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(ceil, v); }
    
    using ::std::round;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> round(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(round, v); }
    
    using ::std::trunc;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> trunc(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(trunc, v); }
    
    //using ::std::clamp;
    //template <length_t L, arithmetic T>
    //constexpr vec<L, T> clamp(const vec<L, T>& v, const vec<L, T>& min, const vec<L, T>& max) { return clamp(v, min, max); }
    
    using ::std::sqrt;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> sqrt(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(sqrt, v); }
    
    using ::std::log;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> log(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(log, v); }
    
    using ::std::exp;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> exp(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(exp, v); }
    
    using ::std::pow;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> pow(const vec<L, T>& v, T s) { return functor_vec_scalar<L, T, T>::call(pow, v, s); }
    
    using ::std::acos;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> acos(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(acos, v); }
    
    using ::std::asin;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> asin(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(asin, v); }   
    
    using ::std::atan;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> atan(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(atan, v); }
    
    using ::std::cos;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> cos(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(cos, v); }
    
    using ::std::sin;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> sin(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(sin, v); }
    
    using ::std::tan;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> tan(const vec<L, T>& v) { return functor_single_vec<L, T, T>::call(tan, v); }
    
    //using ::std::atan2;
    //template <length_t L, arithmetic T>
    //constexpr vec<L, T> atan2(const vec<L, T>& v) { return functor_vec_scalar<L, T, T>::call(atan2, v); }
    
    using ::std::fmod;
    template <length_t L, arithmetic T>
    constexpr vec<L, T> fmod(const vec<L, T>& v, T s) { return functor_vec_scalar<L, T, T>::call(fmod, v, s); }
    
    using ::std::isnan;
    template <length_t L, arithmetic T>
    constexpr vec<L, bool> is_nan(const vec<L, T>& v) { return functor_single_vec<L, bool, T>::call(isnan, v); }
    
    using ::std::isinf;
    template <length_t L, arithmetic T>
    constexpr vec<L, bool> is_inf(const vec<L, T>& v) { return functor_single_vec<L, bool, T>::call(isinf, v); }
}
