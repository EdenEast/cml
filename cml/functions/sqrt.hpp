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
#include <math.h>

namespace cml
{
    namespace implementation
    {
        // https://stackoverflow.com/a/27709195
        template<typename ValueType>
        constexpr ValueType sqrt_impl(ValueType x, ValueType lo, ValueType hi)
        {
            if (lo == hi)
                return lo;

            const ValueType mid = (lo + hi + 1) / 2;

            if (x / mid < mid)
                return sqrt_impl<ValueType>(x, lo, mid - 1);
            else
                return sqrt_impl(x, mid, hi);
        }
    }

    template<typename ValueType>
    constexpr ValueType sqrt(const ValueType& v)
    {
        return implementation::sqrt_impl(v, static_cast<ValueType>(0), v / static_cast<ValueType>(2) + static_cast<ValueType>(1));
    }
}