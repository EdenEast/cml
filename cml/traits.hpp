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

#include "matrix.hpp"
#include "definitions.hpp"
#include "functions/abs.hpp"
#include <limits>

namespace cml
{
    template<typename ValueType>
    struct is_vector : public std::false_type {};

    template<typename ValueType>
    struct is_vector<implementation::matrix<1, 1, ValueType>> : public std::false_type {};

    template<size_t DimX, typename ValueType>
    struct is_vector<implementation::matrix<DimX, 1, ValueType>> : public std::true_type {};

    template<size_t DimY, typename ValueType>
    struct is_vector<implementation::matrix<1, DimY, ValueType>> : public std::true_type {};

    template<typename X>
    struct is_matrix : public std::false_type {};

    template<size_t DimY, size_t DimX, typename ValueType>
    struct is_matrix<implementation::matrix<DimX, DimY, ValueType>> : public std::true_type {};

    template<typename X> struct matrix_traits {};
    template<size_t DimY, size_t DimX, typename ValueType>
    struct matrix_traits<implementation::matrix<DimX, DimY, ValueType>>
    {
        static constexpr uvec2 dim = uvec2{DimX, DimY};
        static constexpr size_t dimx = DimX;
        static constexpr size_t dimy = DimY;
        static constexpr size_t components = DimX * DimY;
        using type = ValueType;
    };

    template<int ulp = 1, typename ValueType>
    constexpr bool is_equal(const ValueType v1, const ValueType v2)
    {
        return abs(v1 - v2) <= std::numeric_limits<ValueType>::epsilon() * abs(v1 + v2) * ulp
            || abs(v1 - v2) <= std::numeric_limits<ValueType>::min();
    }
}
