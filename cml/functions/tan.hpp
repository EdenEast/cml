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

#include "../tau.hpp"
#include "sin.hpp"
#include "cos.hpp"

namespace cml
{
    namespace implementation
    {
        template<typename ValueType>
        constexpr auto tan_impl(const ValueType v) -> ValueType
        {
            static_assert(cos(v) != 0, "cannot calculate tan when cos of value is 0.");
            return sin(v) / cos(v);
        }

        template <typename ValueType>
        constexpr ValueType atan_term(ValueType x, std::size_t k)
        {
            return (ValueType{2} * static_cast<ValueType>(k) * x) / ((ValueType{2} * static_cast<ValueType>(k) + ValueType{1}) * (ValueType{1} + x));
        }

        template <typename ValueType>
        constexpr ValueType atan_product(ValueType x, std::size_t k)
        {
            return k == 1 ? atan_term(x * x, k) : atan_term(x * x, k) * atan_product(x, k - 1);
        }

        template <typename ValueType>
        constexpr ValueType atan_sum(ValueType x, ValueType sum, std::size_t n)
        {
            return sum + atan_product(x, n) == sum ? sum : atan_sum(x, sum + atan_product(x, n), n + 1);
        }

        template<typename ValueType>
        constexpr auto atan_impl(const ValueType v) -> ValueType
        {
            return v / (ValueType{1} + v*v) * atan_sum(v, ValueType{1}, 1);
        }

        template<typename ValueType>
        constexpr auto atan2_impl(ValueType x, ValueType y) -> ValueType
        {
            return x > 0 ? atan_impl(y / x) :
                y >= 0 && x < 0 ? atan_impl(y / x) + pi<ValueType> :
                y < 0 && x < 0 ? atan_impl(y / x) - pi<ValueType> :
                y > 0 && x == 0 ? pi<ValueType> / ValueType{ 2.0l } :
                -pi<ValueType> / ValueType{ 2.0l };
        }
    }

    template<typename ValueType, implementation::angle_kind AK>
    constexpr auto tan(const implementation::angle<ValueType, AK> v) -> ValueType
    {
        return sin(v) / cos(v);
    }

    template<typename ValueType, implementation::angle_kind AK>
    constexpr auto atan(const implementation::angle<ValueType, AK> v) -> ValueType
    {
        return implementation::atan_impl(static_cast<ValueType>(implementation::radian<ValueType>{v}));
    }

    template<typename ValueType>
    constexpr auto atan2(const ValueType x, const ValueType y) -> ValueType
    {
        return implementation::atan2_impl(x, y);
    }

    template<typename ValueType>
    constexpr auto tanh(const ValueType v) -> ValueType
    {
        return sinh(v) / cosh(v);
    }

    template<typename ValueType>
    constexpr auto atanh(const ValueType v) -> ValueType
    {
        return v > -1 && v < 1 ? (ValueType{1}/ValueType{2}) * log((ValueType{1} + v) / (ValueType{1} - v)) : throw std::runtime_error("atanh value is out of the range of [-1,1]");
    }
}

#ifdef CML_COMPILE_TEST_CASE

#include "../definitions.hpp"

static_assert(cml::is_close_zero(0.f, cml::tan(cml::radian<float>(cml::pi<float>))), "tan(0.f)");
static_assert(cml::is_close_zero(0.0, cml::tan(cml::radian<double>(cml::pi<double>))), "tan(0.0");
static_assert(cml::is_close_zero(0.l, cml::tan(cml::radian<long double>(cml::pi<long double>))), "tan(0.l)");

static_assert(cml::is_equal(1.f, cml::tan(cml::radian<float>(cml::pi<float>/4.f))), "tan(pi/4)");
static_assert(cml::is_equal(1.0, cml::tan(cml::radian<double>(cml::pi<double>/4.0))), "tan(pi/4)");
static_assert(cml::is_equal(1.l, cml::tan(cml::radian<long double>(cml::pi<long double>/4.l))), "tan(pi/4)");

// tan(1) == 1.557407724654902230506974807458360173087250772381520038383
static_assert(cml::is_equal(cml::tan(cml::radian<double>(1)), 1.5574077246549022), "tan(1.0)");

static_assert(cml::is_equal(cml::pi<float>/4.f, cml::atan(cml::radian<float>(1))), "atan(1.f)");
static_assert(cml::is_equal(cml::pi<double>/4.0, cml::atan(cml::radian<double>(1))), "atan(1.f)");
static_assert(cml::is_equal(cml::pi<long double>/4.l, cml::atan(cml::radian<long double>(1))), "atan(1.f)");

static_assert(cml::is_equal(cml::pi<float>/4.f, cml::atan2(1.f, 1.f)), "atan2(1,1)");
static_assert(cml::is_equal(cml::pi<double>/4.f, cml::atan2(1.0, 1.0)), "atan2(1,1)");
static_assert(cml::is_equal(cml::pi<long double>/4.f, cml::atan2(1.l, 1.l)), "atan2(1,1)");

// tanh(1) == 0.761594155955764888119458282604793590412768597257936551596
static_assert(cml::is_equal(cml::tanh(1.f), 0.7615941f), "tanh(1)");
static_assert(cml::is_equal(cml::tanh(1.0), 0.7615941559557648), "tanh(1)");
static_assert(cml::is_equal(cml::tanh(1.l), 0.76159415595576488811l), "tanh(1)");

// atanh(pi/4) == 1.059306170823243157230052319189942257188477765993631253524
static_assert(cml::is_equal(cml::atanh(cml::pi<float>/4.f), 1.0593061f), "atanh(pi/4)");
static_assert(cml::is_equal(cml::atanh(cml::pi<double>/4.f), 1.0593061708232431), "atanh(pi/4)");
static_assert(cml::is_equal(cml::atanh(cml::pi<long double>/4.f), 1.05930617082324315723l), "atanh(pi/4)");

#endif
