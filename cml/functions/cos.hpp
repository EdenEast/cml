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

        template<typename ValueType>
        constexpr auto acos_impl(const ValueType v) -> ValueType
        {
            return v == ValueType{-1} ? pi<ValueType> :
                   v == ValueType{1} ? 0 :
                   pi<ValueType> / ValueType{2} -asin_impl(v);
        }
    }

    template<typename ValueType, implementation::angle_kind AK>
    constexpr auto cos(const implementation::angle<ValueType, AK> v) -> ValueType
    {
        return implementation::cos_impl(static_cast<ValueType>(implementation::radian<ValueType>{v}));
    }

    template<typename ValueType, implementation::angle_kind AK>
    constexpr auto acos(const implementation::angle<ValueType, AK> v) -> ValueType
    {
        return implementation::acos_impl(static_cast<ValueType>(implementation::radian<ValueType>{v}));
    }

    template<typename ValueType>
    constexpr auto cosh(const ValueType v) -> ValueType
    {
        return (exp(v) + exp(-v)) / ValueType{2};
    }

    template<typename ValueType>
    constexpr auto acosh(const ValueType v) -> ValueType
    {
        return v >= 1 ? log(v + sqrt(v*v - ValueType{1})) : throw std::runtime_error("acosh is greater then 1");
    }
}

#ifdef CML_COMPILE_TEST_CASE

#include "../definitions.hpp"

static_assert(cml::is_equal(cml::cos(cml::radian<float>(0)), 1.f), "cos(1.f)");
static_assert(cml::is_equal(cml::cos(cml::radian<double>(0)), 1.0), "cos(1.0)");
static_assert(cml::is_equal(cml::cos(cml::radian<long double>(0)), 1.l), "cos(1.l)");

static_assert(cml::is_close_zero(0.f, cml::cos(cml::radian<float>(cml::half_pi<float>))), "cos(0.f)");
static_assert(cml::is_close_zero(0.0, cml::cos(cml::radian<double>(cml::half_pi<double>))), "cos(0.0)");
static_assert(cml::is_close_zero(0.l, cml::cos(cml::radian<long double>(cml::half_pi<long double>))), "cos(0.l)");

// cos(1) == 0.540302305868139717400936607442976603732310420617922227670
static_assert(cml::is_equal(cml::cos(cml::radian<double>(1)), 0.5403023058681397), "cos(1.0)");

static_assert(cml::is_equal(cml::acos(cml::radian<float>(0)), cml::half_pi<float>), "acos(0.f)");
static_assert(cml::is_equal(cml::acos(cml::radian<double>(0)), cml::half_pi<double>), "acos(0.0)");
static_assert(cml::is_equal(cml::acos(cml::radian<long double>(0)), cml::half_pi<long double>), "acos(0.l)");

static_assert(cml::is_close_zero(cml::acos(cml::radian<float>(1)), 0.f), "acos(1.f)");
static_assert(cml::is_close_zero(cml::acos(cml::radian<double>(1)), 0.0), "acos(1.0)");
static_assert(cml::is_close_zero(cml::acos(cml::radian<long double>(1)), 0.l), "acos(1.l)");

static_assert(cml::is_equal(cml::cosh(0.f), 1.f), "cosh(0.f)");
static_assert(cml::is_equal(cml::cosh(0.0), 1.0), "cosh(0.0)");
static_assert(cml::is_equal(cml::cosh(0.l), 1.l), "cosh(0.l)");

static_assert(cml::is_close_zero(0.f, cml::acosh(1.f)), "acosh(1.f)");
static_assert(cml::is_close_zero(0.0, cml::acosh(1.0)), "acosh(1.0)");
static_assert(cml::is_close_zero(0.l, cml::acosh(1.l)), "acosh(1.l)");

#endif
