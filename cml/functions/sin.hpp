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

#include "../angle.hpp"
#include "../equality.hpp"
#include "exp.hpp"
#include "log.hpp"
#include "sqrt.hpp"

namespace cml
{
    namespace implementation
    {
        template<typename ValueType>
        constexpr auto trig_series(const ValueType x, const ValueType sum, const ValueType n, const ValueType i, const ValueType s, const ValueType t) -> ValueType
        {
            return feq(sum, sum + t*s/n) ? sum : trig_series(x, sum + t*s/n, n*i*(i+1), i+2, -s, t*x*x);
        }
        
        template<typename ValueType>
        constexpr auto sin_impl(const ValueType v) -> ValueType
        {
            return trig_series(v, v, ValueType{6}, ValueType{4}, ValueType{-1}, v*v*v);
        }

        template<typename ValueType>
        constexpr auto asin_series(const ValueType x, const ValueType sum, std::size_t n, ValueType t) -> ValueType
        {
            return feq(sum, sum + t * static_cast<ValueType>(n) / (n + ValueType{2})) ? sum : asin_series(x, sum + t * static_cast<ValueType>(n) / (n + ValueType{2}), n + ValueType{2},
                t*x*x*static_cast<ValueType>(n) / (n + ValueType{3}));
        }

        template<typename ValueType>
        constexpr auto asin_impl(const ValueType x) -> ValueType
        {
            return x == ValueType{-1} ? pi<ValueType> / ValueType{-2} :
                   x == ValueType{1} ? pi<ValueType> / ValueType{2} :
                   asin_series(x, x, 1, x*x*x / ValueType{2});
        }
    }

    template<typename ValueType, implementation::angle_kind AK>
    constexpr auto sin(const implementation::angle<ValueType, AK> v) -> ValueType
    {
        return implementation::sin_impl(static_cast<ValueType>(implementation::radian<ValueType>{v}));
    }

    template<typename ValueType, implementation::angle_kind AK>
    constexpr auto asin(const implementation::angle<ValueType, AK> v)->ValueType
    {
        return implementation::asin_impl(static_cast<ValueType>(implementation::radian<ValueType>{v}));
    }

    template<typename ValueType>
    constexpr auto sinh(const ValueType v) -> ValueType
    {
        return (exp(v) - exp(-v)) / ValueType{2};
    }

    template<typename ValueType>
    constexpr auto asinh(const ValueType v) -> ValueType
    {
        return log(v + sqrt(v * v + ValueType{1}));
    }
}

#ifdef CML_COMPILE_TEST_CASE

#include "../definitions.hpp"

// static_assert(cml::is_equal<16>(0.0f, cml::sin(cml::radian<float>(cml::pi<float>))), "sin(TAUf)");
// static_assert(cml::feq(0.0,  cml::sin(cml::radian<double>(cml::pi<double>))), "sin(TAU)");
// static_assert(cml::feq(0.0l, cml::sin(cml::radian<long double>(cml::pi<long double>))), "sin(TAUl)");
// 
// static_assert(cml::is_equal(0.0f, cml::sin(cml::rad(cml::pi<float>))), "sin(PIf)");
// static_assert(cml::is_equal(0.0,  cml::sin(cml::rad(cml::pi<double>))), "sin(PI)");
// static_assert(cml::is_equal(0.0l, cml::sin(cml::rad(cml::pi<long double>))), "sin(PIl)");
// 
// static_assert(cml::is_equal(1.0f, cml::sin(cml::rad(cml::half_pi<float>))), "sin(PI/2f)");
// static_assert(cml::is_equal(1.0,  cml::sin(cml::rad(cml::half_pi<double>))), "sin(PI/2)");
// static_assert(cml::is_equal(1.0l, cml::sin(cml::rad(cml::half_pi<long double>))), "sin(PI/2l)");

// sin(1) = 0.8414709848078965066525
// static_assert(cml::is_equal(0.8414709848078965, cml::sin(cml::rad(1.0))), "sin(1.0)");

#endif
