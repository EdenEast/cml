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

#include "exp.hpp"

namespace cml
{
    namespace implementation
    {
        template<typename ValueType>
        constexpr auto log_iter(const ValueType x, const ValueType y) -> ValueType
        {
            return y + ValueType{2} * (x - exp(y)) / (x + exp(y));
        }

        template<typename ValueType>
        constexpr auto log_helper(const ValueType x, const ValueType y) -> ValueType
        {
            return is_equal(y, log_iter(x, y)) ? y : log_helper(x, log_iter(x, y));
        }

        template<typename ValueType>
        constexpr ValueType log_e{2.71828182845904523536l};

        template<typename ValueType>
        constexpr auto log_gt(const ValueType v) -> ValueType
        {
            auto e = log_e<ValueType>;
            return v > ValueType{0.25} ? log_helper(v, ValueType{0}) : log_gt(v * e * e * e * e * e) - ValueType{5};
        }

        template<typename ValueType>
        constexpr auto log_lt(const ValueType v) -> ValueType
        {
            auto e = log_e<ValueType>;
            return v < ValueType{1024} ? log_helper(v, ValueType{0}) : log_lt(v / (e * e * e * e * e)) + ValueType{5};
        }
    }

    template<typename ValueType>
    constexpr auto log(const ValueType x, const ValueType y) -> ValueType
    {
        return implementation::log_helper(x, y);
    }

    template<typename ValueType>
    constexpr auto log(const ValueType v) -> ValueType
    {
        return v >= ValueType{1024} ? implementation::log_lt(v) : implementation::log_gt(v);
    }
}
