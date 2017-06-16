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

namespace cml
{
    namespace implementation
    {
        template<typename VT> struct get_iterator_number { static constexpr size_t count = sizeof(VT) * 8; };
        template<> struct get_iterator_number<float> { static constexpr size_t count = 24; };
        template<> struct get_iterator_number<double> { static constexpr size_t count = 53; };

        template<typename ValueType>
        constexpr ValueType sqrt_impl(ValueType number)
        {
            ValueType res = number;
            ValueType it = number;
            for (size_t i = 0; i < get_iterator_number<ValueType>::count; ++i)
            {
                it /= ValueType(2);
                const ValueType pow = res * res;
                if (pow == number)
                    break;
                else if (pow > number)
                    res -= it;
                else
                    res += it;
            }
            return res;
        }
    }

    template<typename ValueType>
    constexpr ValueType sqrt(ValueType&& v)
    {
        return implementation::sqrt_impl(v);
    }
}

#ifdef CML_COMPILE_TEST_CASE

#include "../traits.hpp"

static_assert(cml::equals_approx<16>(5.0, cml::sqrt(5.0) * cml::sqrt(5.0)));
static_assert(5.0f == cml::sqrt(5.0f) * cml::sqrt(5.0f));

#endif
