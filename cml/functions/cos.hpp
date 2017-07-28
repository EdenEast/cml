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

#include "sin.hpp"

namespace cml
{
    namespace implementation
    {
        template<typename ValueType>
        constexpr auto cos_impl(const ValueType v) -> ValueType
        {
            return trig_series(v, ValueType{1}, ValueType{2}, ValueType{3}, ValueType{-1}, v*v);
        }
    }
    
    template<typename ValueType>
    constexpr auto cos(const implementation::radian<ValueType> v) -> ValueType
    {
        return implementation::cos_impl(static_cast<ValueType>(v));
    }
    
    template<typename ValueType>
    constexpr auto cos(const implementation::degree<ValueType>& v) -> ValueType
    {
        return cos(implementation::radian<ValueType>{v});
    }
}
