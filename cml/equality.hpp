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

#include "functions/abs.hpp"
#include "functions/max.hpp"
#include <limits>

namespace cml
{
    template<typename VT, typename ST>
    constexpr auto is_close(const VT& a, const ST& b)
    {
        return abs(a - b) <= std::numeric_limits<std::conditional_t<sizeof(VT) <= sizeof(ST), VT, ST>>::epsilon() * max(abs(a), abs(b));
    }
    
    template<int ulp = 1, typename ValueType>
    constexpr bool is_equal(const ValueType v1, const ValueType v2)
    {
        return abs(v1 - v2) <= std::numeric_limits<ValueType>::epsilon() * abs(v1 + v2) * ulp
            || abs(v1 - v2) <= std::numeric_limits<ValueType>::min();
    }
}
