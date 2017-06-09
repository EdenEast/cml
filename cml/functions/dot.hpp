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

namespace cml
{
    namespace implementation
    {
        template<typename ValueType, size_t DimX, size_t DimY, size_t... Idxs>
        constexpr ValueType dot_impl(std::index_sequence<Idxs...>, const implementation::matrix<DimX, DimY, ValueType> &v1, const implementation::matrix<DimX, DimY, ValueType> &v2)
        {
#ifndef _MSC_VER
            return ((v1.components[Idxs] * v2.components[Idxs]) + ...);
#else
            ValueType ret = ValueType(0);
            using ar_t = int[];
            (void)(ar_t {((ret += v1.components[Idxs] * v2.components[Idxs]), 0)...});
            return ret;
#endif
        }
    } // namespace implementation

    template<typename ValueType, size_t DimX, size_t DimY>
    constexpr ValueType dot(const implementation::matrix<DimX, DimY, ValueType>& v1, const implementation::matrix<DimX, DimY, ValueType>& v2)
    {
        static_assert(DimX == 1 || DimY == 1, "you can only perform dot products on vectors");
        constexpr size_t dim = (DimX == 1 ? DimY : DimX);

        return implementation::dot_impl(std::make_index_sequence<dim>{}, v1, v2);
    }
} // namespace cml
