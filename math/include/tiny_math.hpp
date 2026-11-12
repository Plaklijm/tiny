#pragma once

#include "vec.hpp"
#include "math_operations.hpp"
#include "common.hpp"

// https://wumbo.net/

namespace tiny::math
{
    using vector2d  = vec<2, float>;
    using dvector2d = vec<2, double>;
    using ivector2d = vec<2, int>;
    
    using vector3d  = vec<3, float>;
    using dvector3d = vec<3, double>;
    using ivector3d = vec<3, int>;
    
    using vector4d  = vec<4, float>;
    using dvector4d = vec<4, double>;
    using ivector4d = vec<4, int>;
    
    using matrix2x2 = mat<2, 2, float>;
    using dmattrix2x2 = mat<2, 2, double>;
    using imatrix2x2 = mat<2, 2, int>;
    
    using matrix3x3 = mat<3, 3, float>;
    using dmatrix3x3 = mat<3, 3, double>;
    using imatrix3x3 = mat<3, 3, int>;
    
    using matrix4x4 = mat<4, 4, float>;
    using dmatrix4x4 = mat<4, 4, double>;
    using imatrix4x4 = mat<4, 4, int>;
    
    using quaternion = quat<float>;
    using dquaternion = quat<double>;
}