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

#include "angle_kind.hpp"
#include "traits.hpp"
#include "equality.hpp"

namespace cml::implementation
{
    template<typename ValueType, angle_kind Kind>
    class angle
    {
        static_assert(std::is_floating_point<ValueType>::value || is_fixed_point<ValueType>::value, "ValueType must be a floating|fixed point.");
    public:
        using value_type = ValueType;
        using this_type = angle<ValueType, Kind>;

        constexpr angle() noexcept = default;
        constexpr angle(const this_type& other) noexcept
        : value(other.value)
        {
        }

        explicit constexpr angle(ValueType value) noexcept
        : value(value)
        {
        }

        template<angle_kind DiffKind>
        constexpr angle(angle<ValueType, DiffKind> other) noexcept
        : value(static_cast<ValueType>(other) * angle_convert_factor<ValueType, DiffKind, Kind>::factor)
        {
        }

        constexpr this_type& operator=(this_type a) noexcept
        {
            value = a.value;
            return *this;
        }

        template<angle_kind DiffKind>
        constexpr this_type& operator=(angle<ValueType, DiffKind> other) noexcept
        {
            value = other.value * angle_convert_factor<ValueType, DiffKind, Kind>::factor;
            return *this;
        }

        explicit constexpr operator ValueType() const
        {
            return value;
        }

        template<angle_kind DiffKind>
        constexpr operator angle<ValueType, DiffKind>() const
        {
            return angle<ValueType, DiffKind>(*this);
        }

        constexpr this_type operator+(const this_type a) const
        {
            return this_type(value + a.value);
        }

        constexpr this_type operator-(const this_type a) const
        {
            return this_type(value - a.value);
        }

        constexpr this_type operator-() const
        {
            return this_type(-value);
        }

        constexpr this_type operator*(const this_type a) const
        {
            return this_type(value * a.value);
        }

        constexpr this_type operator/(const this_type a) const
        {
            return this_type(value / a.value);
        }

        constexpr this_type operator*(const ValueType val) const
        {
            return this_type(value * val);
        }

        constexpr this_type operator/(const ValueType val) const
        {
            return this_type(value / val);
        }

        constexpr bool operator==(const this_type a) const
        {
            return is_equal(value, a.value);
        }

        template<angle_kind DiffKind>
        constexpr bool operator==(const angle<ValueType, DiffKind> other) const
        {
            return is_equal(value, static_cast<ValueType>(this_type(other)));
        }

        constexpr bool operator!=(const this_type a) const
        {
            return !(*this == a);
        }

        template<angle_kind DiffKind>
        constexpr bool operator!=(const angle<ValueType, DiffKind> a) const
        {
            return !(*this == a);
        }

        constexpr bool operator<(const this_type a) const
        {
            return value < a.value;
        }

        constexpr bool operator>(const this_type a) const
        {
            return value > a.value;
        }

        constexpr this_type& operator+=(const ValueType val)
        {
            value += val;
            return *this;
        }

        constexpr this_type& operator+=(const this_type a)
        {
            value += a.value;
            return *this;
        }

        constexpr this_type& operator-=(const ValueType val)
        {
            value -= val;
            return *this;
        }

        constexpr this_type& operator-=(const this_type a)
        {
            value -= a.value;
            return *this;
        }

        constexpr this_type& operator*=(const ValueType val)
        {
            value *= val;
            return *this;
        }

        constexpr this_type& operator*=(const this_type a)
        {
            value *= a.value;
            return *this;
        }

        constexpr this_type& operator/=(const ValueType val)
        {
            value /= val;
            return *this;
        }

        constexpr this_type& operator/=(const this_type a)
        {
            value /= a.value;
            return *this;
        }

    private:
        ValueType value = ValueType{0};
    };

    template<typename ValueType>
    using degree = angle<ValueType, angle_kind::degree>;

    template<typename ValueType>
    using radian = angle<ValueType, angle_kind::radian>;
} // namespace cml::implementation

#ifdef CML_COMPILE_TEST_CASE

static_assert(cml::implementation::degree<float>(90.0f) == cml::implementation::degree<float>(cml::implementation::radian<float>(cml::implementation::degree<float>(90.0f))));
static_assert(cml::implementation::degree<double>(45.0) == cml::implementation::radian<double>(cml::implementation::degree<double>(45.0)));

#endif
