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
        template<size_t DimX, size_t DimY, typename ValueType, size_t... Idxs>
        constexpr ValueType length_impl(std::index_sequence<Idxs...>, const implementation::matrix<DimX, DimY, ValueType>& v)
        {
#ifndef _MSC_VER
            return sqrt(((v.components[Idxs] * v.components[Idxs]) + ...));
#else
            Valuetype ret = Valuetype(0);
            using ar_t = int[];
            (void)(ar_t {((ret += v.components[Idxs] * v.components[Idxs]), 0)...});
#endif
        }
    }
    
    template<size_t DimX, size_t DimY, typename ValueType>
    constexpr ValueType length(const implementation::matrix<DimX, DimY, ValueType>& v)
    {
        static_assert(is_vector(v), "Cannot find the length of a matrix. Make sure that the value passed is a vector");
        return length_impl(std::make_index_sequence<get_vector_size(v)>{}, v);
    }
}


#ifdef CML_COMPILE_TEST_CASE

static_assert(cml::equals_approx<32>(cml::length(cml::implementation::matrix<2, 1, float>(6.f, 8.f)), 10.f));
static_assert(cml::equals_approx<16>(cml::length(cml::implementation::matrix<2, 1, double>(6.0, 8.0)), 10.0));

#endif
