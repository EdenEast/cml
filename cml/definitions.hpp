//
// Copyright (c) 2017 James Simpson, Timothée Feuillet
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#pragma once

#include "matrix_kind.hpp"

namespace cml
{
    namespace implementation
    {
        template<size_t DimX, size_t DimY, typename ValueType, matrix_kind Kind> class matrix;
        template<typename ValueType> class degree;
        template<typename ValueType> class radian;
    }

    // Fixed points
    template<typename Type, size_t FractionnalBits> struct fixed;

    using f88 = fixed<int16_t, 8>;
    using uf88 = fixed<uint16_t, 8>;

    using f1616 = fixed<int32_t, 16>;
    using uf1616 = fixed<uint32_t, 16>;

    /// @brief numbers from ]-127:127[ with 24bit of precision (epsilon of 0.00000005960464477539063)
    using f0824 = fixed<int32_t, 24>;
    /// @brief numbers from [0:257[ with 24bit of precision (epsilon of 0.00000005960464477539063)
    using uf0824 = fixed<uint32_t, 24>;

    /// @brief numbers from ]-1:1[ with 31 bits of precision (epsilon of 0.0000000002328306437080797)
    /// nice for colors and values in the -1:1 range (normalized vectors, ...)
    using f0131 = fixed<int32_t, 31>;
    /// @brief numbers from [0:1[ with 32 bits of precision (epsilon of 0.0000000002328306436538696)
    /// nice for colors and values in the 0:1 range (normalized vectors, ...)
    using uf0032 = fixed<uint32_t, 32>;

    // Vectors
    template<size_t Dim, typename ValueType>
    using vector = implementation::matrix<Dim, 1, ValueType, implementation::matrix_kind::normal>;

    using vec2  = vector<2, float>;
    using cvec2 = vector<2, int8_t>;
    using ucvec2 = vector<2, uint8_t>;
    using svec2 = vector<2, int16_t>;
    using usvec2 = vector<2, uint16_t>;
    using uvec2 = vector<2, uint32_t>;
    using ivec2 = vector<2, int32_t>;
    using dvec2 = vector<2, double>;
    using f88vec2 = vector<2, f88>;
    using uf88vec2 = vector<2, uf88>;
    using f1616vec2 = vector<2, f1616>;
    using uf1616vec2 = vector<2, uf1616>;
    using f0824vec2 = vector<2, f0824>;
    using uf0824vec2 = vector<2, uf0824>;
    using f0131vec2 = vector<2, f0131>;
    using uf0032vec2 = vector<2, uf0032>;

    using vec3  = vector<3, float>;
    using cvec3 = vector<3, int8_t>;
    using ucvec3 = vector<3, uint8_t>;
    using svec3 = vector<3, int16_t>;
    using usvec3 = vector<3, uint16_t>;
    using uvec3 = vector<3, uint32_t>;
    using ivec3 = vector<3, int32_t>;
    using dvec3 = vector<3, double>;
    using f88vec3 = vector<3, f88>;
    using uf88vec3 = vector<3, uf88>;
    using f1616vec3 = vector<3, f1616>;
    using uf1616vec3 = vector<3, uf1616>;
    using f0824vec3 = vector<3, f0824>;
    using uf0824vec3 = vector<3, uf0824>;
    using f0131vec3 = vector<3, f0131>;
    using uf0032vec3 = vector<3, uf0032>;

    using vec4  = vector<4, float>;
    using cvec4 = vector<4, int8_t>;
    using ucvec4 = vector<4, uint8_t>;
    using svec4 = vector<4, int16_t>;
    using usvec4 = vector<4, uint16_t>;
    using uvec4 = vector<4, uint32_t>;
    using ivec4 = vector<4, int32_t>;
    using dvec4 = vector<4, double>;
    using f88vec4 = vector<4, f88>;
    using uf88vec4 = vector<4, uf88>;
    using f1616vec4 = vector<4, f1616>;
    using uf1616vec4 = vector<4, uf1616>;
    using f0824vec4 = vector<4, f0824>;
    using uf0824vec4 = vector<4, uf0824>;
    using f0131vec4 = vector<4, f0131>;
    using uf0032vec4 = vector<4, uf0032>;

    // Matrix
    template<size_t X, size_t Y>
    using mat = implementation::matrix<X, Y, float, implementation::matrix_kind::normal>;
    template<size_t X, size_t Y>
    using imat = implementation::matrix<X, Y, int32_t, implementation::matrix_kind::normal>;
    template<size_t X, size_t Y>
    using smat = implementation::matrix<X, Y, int16_t, implementation::matrix_kind::normal>;
    template<size_t X, size_t Y>
    using dmat = implementation::matrix<X, Y, double, implementation::matrix_kind::normal>;

    template<size_t X, size_t Y>
    using f88mat = implementation::matrix<X, Y, f88, implementation::matrix_kind::normal>;
    template<size_t X, size_t Y>
    using f1616mat = implementation::matrix<X, Y, f1616, implementation::matrix_kind::normal>;
    template<size_t X, size_t Y>
    using f0824mat = implementation::matrix<X, Y, f0824, implementation::matrix_kind::normal>;
    template<size_t X, size_t Y>
    using f0131mat = implementation::matrix<X, Y, f0131, implementation::matrix_kind::normal>;

    using mat2 = mat<2, 2>;
    using mat3 = mat<3, 3>;
    using mat4 = mat<4, 4>;

    using dmat2 = dmat<2, 2>;
    using dmat3 = dmat<3, 3>;
    using dmat4 = dmat<4, 4>;

    using imat2 = imat<2, 2>;
    using imat3 = imat<3, 3>;
    using imat4 = imat<4, 4>;

    using smat2 = smat<2, 2>;
    using smat3 = smat<3, 3>;
    using smat4 = smat<4, 4>;

    using f88mat2 = f88mat<2, 2>;
    using f88mat3 = f88mat<3, 3>;
    using f88mat4 = f88mat<4, 4>;

    using f1616mat2 = f1616mat<2, 2>;
    using f1616mat3 = f1616mat<3, 3>;
    using f1616mat4 = f1616mat<4, 4>;

    using f0824mat2 = f0824mat<2, 2>;
    using f0824mat3 = f0824mat<3, 3>;
    using f0824mat4 = f0824mat<4, 4>;

    using f0131mat2 = f0131mat<2, 2>;
    using f0131mat3 = f0131mat<3, 3>;
    using f0131mat4 = f0131mat<4, 4>;

    // Scalar
    template<typename ValueType>
    using scalar = implementation::matrix<1, 1, ValueType, implementation::matrix_kind::normal>;

    using iscalar = scalar<int32_t>;
    using uscalar = scalar<uint32_t>;
    using fscalar = scalar<float>;
    using dscalar = scalar<double>;

    using f88scalar = scalar<f88>;
    using f1616scalar = scalar<f1616>;
    using f0824scalar = scalar<f0824>;
    using f0131scalar = scalar<f0131>;

    using uf88scalar = scalar<uf88>;
    using uf1616scalar = scalar<uf1616>;
    using uf0824scalar = scalar<uf0824>;
    using uf0032scalar = scalar<uf0032>;

    // Angle
    using deg = implementation::degree<float>;
    using rad = implementation::radian<float>;
    using ddeg = implementation::degree<double>;
    using drad = implementation::radian<double>;

    using f88deg = implementation::degree<f88>;
    using f88rad = implementation::radian<f88>;
    using f1616deg = implementation::degree<f1616>;
    using f1616rad = implementation::radian<f1616>;
    using f0824deg = implementation::degree<f0824>;
    using f0824rad = implementation::radian<f0824>;

    using uf88deg = implementation::degree<uf88>;
    using uf88rad = implementation::radian<uf88>;
    using uf1616deg = implementation::degree<uf1616>;
    using uf1616rad = implementation::radian<uf1616>;
    using uf0824deg = implementation::degree<uf0824>;
    using uf0824rad = implementation::radian<uf0824>;
    using uf0032deg = implementation::degree<uf0032>;
    using uf0032rad = implementation::radian<uf0032>;
} // namespace cml
