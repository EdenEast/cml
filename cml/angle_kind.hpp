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

#include "tau.hpp"

namespace cml::implementation
{
    enum class angle_kind
    {
        degree,
        radian
    };

    template<typename ValueType, angle_kind From, angle_kind To>
    struct angle_convert_factor
    {
        static constexpr ValueType factor = ValueType(1);
    };

    template<typename ValueType, angle_kind A>
    struct angle_convert_factor<ValueType, A, A>
    {
        static constexpr ValueType factor = ValueType(1);
    };

    template<typename ValueType>
    struct angle_convert_factor<ValueType, angle_kind::degree, angle_kind::radian>
    {
        static constexpr ValueType factor = tau<ValueType> / ValueType(360);
    };

    template<typename ValueType>
    struct angle_convert_factor<ValueType, angle_kind::radian, angle_kind::degree>
    {
        static constexpr ValueType factor = ValueType(360) / tau<ValueType>;
    };
}
