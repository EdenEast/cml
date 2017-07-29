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

#include <cstddef>
#include "../traits.hpp"
#include "../equality.hpp"

namespace cml
{
    namespace implementation
    {
        template<typename ValueType>
        constexpr auto sqrt_helper(const ValueType& a, const ValueType& b) -> ValueType
        {
            return is_close(a, b * b) ? b : sqrt_helper(a, (b + a / b) / ValueType{2});
        }
    }

    template<typename ValueType>
    constexpr auto sqrt(ValueType v) -> ValueType
    {
        return implementation::sqrt_helper(v, v);
    }
}

#ifdef CML_COMPILE_TEST_CASE

#include "../traits.hpp"

static_assert(cml::is_equal(5.0, cml::sqrt(5.0) * cml::sqrt(5.0)));
static_assert(5.0f == cml::sqrt(5.0f) * cml::sqrt(5.0f));

#endif
