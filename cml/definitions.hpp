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


namespace cml
{
    namespace implementation
    {
        template<size_t DimX, size_t DimY, typename ValueType> class matrix;
    }

    // Vectors
    template<size_t Dim, typename ValueType>
    using vector = implementation::matrix<Dim, 1, ValueType>;

    using vec2  = vector<2, float>;
    using cvec2 = vector<2, uint8_t>;
    using uvec2 = vector<2, uint32_t>;
    using ivec2 = vector<2, int32_t>;
    using dvec2 = vector<2, double>;

    using vec3  = vector<3, float>;
    using cvec3 = vector<3, uint8_t>;
    using uvec3 = vector<3, uint32_t>;
    using ivec3 = vector<3, int32_t>;
    using dvec3 = vector<3, double>;

    using vec4  = vector<4, float>;
    using cvec4 = vector<4, uint8_t>;
    using uvec4 = vector<4, uint32_t>;
    using ivec4 = vector<4, int32_t>;
    using dvec4 = vector<4, double>;

    // Matrix
    template<size_t X, size_t Y>
    using mat = implementation::matrix<X, Y, float>;
    template<size_t X, size_t Y>
    using imat = implementation::matrix<X, Y, int32_t>;
    template<size_t X, size_t Y>
    using dmat = implementation::matrix<X, Y, double>;

    using mat2 = mat<2, 2>;
    using mat3 = mat<3, 3>;
    using mat4 = mat<4, 4>;

    using dmat2 = dmat<2, 2>;
    using dmat3 = dmat<3, 3>;
    using dmat4 = dmat<4, 4>;

    using imat2 = imat<2, 2>;
    using imat3 = imat<3, 3>;
    using imat4 = imat<4, 4>;
} // namespace cml
