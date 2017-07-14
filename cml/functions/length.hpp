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

#include "../matrix.hpp"
#include "../traits.hpp"
#include "sqrt.hpp"

namespace cml
{
    namespace implementation
    {
        template<size_t DimX, size_t DimY, typename ValueType, matrix_kind Kind, size_t... Idxs>
        constexpr ValueType length_impl(std::index_sequence<Idxs...>, const matrix<DimX, DimY, ValueType, Kind>& v)
        {
#ifndef _MSC_VER
            return sqrt(((v.components[Idxs] * v.components[Idxs]) + ...));
#else
            ValueType ret = ValueType(0);
            using ar_t = int[];
            (void)(ar_t{((ret += v.components[Idxs] * v.components[Idxs]), 0)...});
            return sqrt(ret);
#endif
        }
    }

    template<size_t DimX, size_t DimY, typename ValueType, implementation::matrix_kind Kind>
    constexpr ValueType length(const implementation::matrix<DimX, DimY, ValueType, Kind>& v)
    {
        static_assert(is_vector<implementation::matrix<DimX, DimY, ValueType, Kind>>::value, "Cannot find the length of a matrix. Make sure that the value passed is a vector");
        constexpr size_t dim = (DimX == 1 ? DimY : DimX);
        return length_impl(std::make_index_sequence<dim>{}, v);
    }
}


#ifdef CML_COMPILE_TEST_CASE

static_assert(cml::is_equal<2>(cml::length(cml::implementation::matrix<2, 1, float, cml::implementation::matrix_kind::normal>(6.f, 8.f)), 10.f));
static_assert(cml::is_equal(cml::length(cml::implementation::matrix<2, 1, double, cml::implementation::matrix_kind::normal>(6.0, 8.0)), 10.0));

#endif
