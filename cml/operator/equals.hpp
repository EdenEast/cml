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

#include <type_traits>

#include "equals_impl.hpp"
#include "../matrix.hpp"
#include "../traits.hpp"

namespace cml::implementation
{
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr bool operator == (const matrix<DimX, DimY, VType, Kind>& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_ms_eq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else if constexpr (std::is_same<matrix<DimX, DimY, VType, Kind>, SType>::value)
            return matrix_mm_eq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return false;
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind>
    constexpr bool operator == (VType&& v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
        return matrix_sm_eq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }
}
