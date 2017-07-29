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
#include "definitions.hpp"
#include "reference.hpp"
#include <type_traits>
#include <limits>

namespace cml
{
    namespace implementation
    {
        template<size_t DimX, size_t DimY, typename ValueType, matrix_kind Kind> class matrix;
    }

    template<typename ValueType>
    struct is_vector : public std::false_type {};

    template<typename ValueType, implementation::matrix_kind Kind>
    struct is_vector<implementation::matrix<1, 1, ValueType, Kind>> : public std::false_type {};

    template<size_t DimX, typename ValueType, implementation::matrix_kind Kind>
    struct is_vector<implementation::matrix<DimX, 1, ValueType, Kind>> : public std::true_type {};

    template<size_t DimY, typename ValueType, implementation::matrix_kind Kind>
    struct is_vector<implementation::matrix<1, DimY, ValueType, Kind>> : public std::true_type {};

    template<typename X>
    struct is_matrix : public std::false_type {};

    template<size_t DimY, size_t DimX, typename ValueType, implementation::matrix_kind Kind>
    struct is_matrix<implementation::matrix<DimX, DimY, ValueType, Kind>> : public std::true_type {};

    template<typename X> struct matrix_traits {};
    template<size_t DimY, size_t DimX, typename ValueType, implementation::matrix_kind Kind>
    struct matrix_traits<implementation::matrix<DimX, DimY, ValueType, Kind>>
    {
        static constexpr uvec2 dim = uvec2{DimX, DimY};
        static constexpr size_t dimx = DimX;
        static constexpr size_t dimy = DimY;
        static constexpr size_t components = DimX * DimY;
        static constexpr implementation::matrix_kind kind = Kind;
        using type = ValueType;
    };

    template<typename T>
    struct remove_matrix_reference
    {
        using type = T;
    };

    template<size_t DimY, size_t DimX, typename ValueType, implementation::matrix_kind Kind>
    struct remove_matrix_reference<implementation::matrix<DimX, DimY, ValueType, Kind>>
    {
        using type = implementation::matrix<DimX, DimY, typename implementation::remove_reference<ValueType>::type, Kind>;
    };

    template<typename T>
    using remove_matrix_reference_t = typename remove_matrix_reference<T>::type;
}
