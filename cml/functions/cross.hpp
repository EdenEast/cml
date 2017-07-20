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
#include "../matrix_operators.hpp"
#include "max.hpp"

namespace cml
{
    namespace implementation
    {
        template<typename ValueType>
        constexpr auto cross_impl(const ValueType& v1, const ValueType& v2) -> auto
        {
            return ValueType(v1.components[1] * v2.components[2] - v1.components[2] * v2.components[1],
                             v1.components[2] * v2.components[0] - v1.components[0] * v2.components[2],
                             v1.components[0] * v2.components[1] - v1.components[1] * v2.components[0]);
        }
    }
    
    template<typename ValueType>
    constexpr auto cross(const ValueType& v1, const ValueType& v2) -> auto
    {
        static_assert(is_vector<ValueType>::value, "can only cross vectors");
        static_assert(max(matrix_traits<ValueType>::dimx, matrix_traits<ValueType>::dimy) == 3, "can only cross 3 component vectors");
        return implementation::cross_impl(v1, v2);
    }
}

#ifdef CML_COMPILE_TEST_CASE

#include "../definitions.hpp"

static_assert(cml::cross(cml::vec3(3, -3, 1), cml::vec3(4, 9, 2)) == cml::vec3(-15, -2, 39));
static_assert(cml::cross(cml::dvec3(3, -3, 1), cml::dvec3(-12, 12, -4)) == cml::dvec3());

#endif
