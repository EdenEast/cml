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
#include "../equality.hpp"
#include <cstdint>

namespace cml
{
    namespace implementation
    {
        template<typename ValueType>
        constexpr auto exp_impl(ValueType x, ValueType sum, ValueType n, std::size_t i, ValueType t) -> ValueType
        {
            return is_equal(sum, sum + t / n) ? sum : exp_impl(x, sum + t / n, n * static_cast<ValueType>(i), i + 1, t * x);
        }
    }

    template<typename ValueType>
    constexpr auto exp(ValueType v) -> ValueType
    {
        return implementation::exp_impl(v, ValueType{1}, ValueType{1}, 2, v);
    }
}

#ifdef CML_COMPILE_TEST_CASE

// e = 2.718281828459045235360
static_assert(cml::is_equal(2.718282f, cml::exp(1.0f)), "exp(1.0f)");
static_assert(cml::is_equal(2.7182818284590454, cml::exp(1.0)), "exp(1.0)");
static_assert(cml::is_equal(2.7182818284590452354l, cml::exp(1.0l)), "exp(1.0l)");

#endif
