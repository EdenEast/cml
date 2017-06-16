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
#include "length.hpp"

namespace cml
{
    template<size_t DimX, size_t DimY, typename ValueType>
    constexpr implementation::matrix<DimX, DimY, ValueType> normalize(const implementation::matrix<DimX, DimY, ValueType>& v)
    {
        static_assert(is_vector(v), "Can only normalize a vector.");
        return v * (ValueType(1) / length(v));
    }
}

#ifdef CML_COMPILE_TEST_CASE

#include "../definitions.hpp"

static_assert(cml::equals_approx<2>(cml::length(cml::normalize(cml::vec3(1, 2, 3))), 1.0f));

#endif
