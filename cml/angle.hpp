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

#include "traits.hpp"

namespace cml::implementation
{
    template<typename ValueType>
    class degree;

    template<typename ValueType>
    class radian;

    template<typename ValueType>
    class degree
    {
        static constexpr ValueType Rad2Deg = static_cast<ValueType>(57.295779513082321);
        static_assert(std::is_floating_point<ValueType>::value || is_fixed_point<ValueType>::value, "ValueType must be a floating|fixed point.");
    public:
        using value_type = ValueType;
        using this_type = degree<ValueType>;

        constexpr degree() noexcept = default;
        constexpr degree(const this_type& other) noexcept
        : angle(other.angle)
        {
        }

        explicit constexpr degree(ValueType deg) noexcept
        : angle(deg)
        {
        }

        explicit constexpr degree(const radian<ValueType>& rad) noexcept
        : degree(static_cast<ValueType>(rad) * Rad2Deg)
        {
        }

        constexpr this_type& operator=(const this_type& deg) noexcept
        {
            angle = deg.angle;
            return *this;
        }

        explicit constexpr operator ValueType() const
        {
            return angle;
        }

        constexpr this_type operator+(const this_type deg) const
        {
            return this_type(angle + deg.angle);
        }

        constexpr this_type operator-(const this_type deg) const
        {
            return this_type(angle - deg.angle);
        }

        constexpr this_type operator-() const
        {
            return this_type(-angle);
        }

        constexpr this_type operator*(const this_type deg) const
        {
            return this_type(angle * deg.angle);
        }

        constexpr this_type operator/(const this_type deg) const
        {
            return this_type(angle / deg.angle);
        }

        constexpr this_type operator*(const ValueType value) const
        {
            return this_type(angle * value);
        }

        constexpr this_type operator/(const ValueType value) const
        {
            return this_type(angle / value);
        }

        constexpr bool operator==(const this_type deg) const
        {
            return is_equal(angle, deg.angle);
        }

        constexpr bool operator==(const radian<ValueType> rad) const
        {
            return is_equal(angle, static_cast<ValueType>(this_type(rad)));
        }

        constexpr bool operator!=(const this_type deg) const
        {
            return !(*this == deg);
        }

        constexpr bool operator!=(const radian<ValueType> rad) const
        {
            return !(*this == rad);
        }

        constexpr bool operator<(const this_type deg) const
        {
            return angle < deg.angle;
        }

        constexpr bool operator>(const this_type deg) const
        {
            return angle > deg.angle;
        }

        constexpr this_type& operator+=(const ValueType val)
        {
            angle += val;
            return *this;
        }

        constexpr this_type& operator+=(const this_type deg)
        {
            angle += deg.angle;
            return *this;
        }

        constexpr this_type& operator-=(const ValueType val)
        {
            angle -= val;
            return *this;
        }

        constexpr this_type& operator-=(const this_type deg)
        {
            angle -= deg.angle;
            return *this;
        }

        constexpr this_type& operator*=(const ValueType val)
        {
            angle *= val;
            return *this;
        }

        constexpr this_type& operator*=(const this_type deg)
        {
            angle *= deg.angle;
            return *this;
        }

        constexpr this_type& operator/=(const ValueType val)
        {
            angle /= val;
            return *this;
        }

        constexpr this_type& operator/=(const this_type deg)
        {
            angle /= deg.angle;
            return *this;
        }

    private:
        ValueType angle = static_cast<ValueType>(0);
    };

    template<typename ValueType>
    class radian
    {
        static constexpr ValueType Deg2Rad = static_cast<ValueType>(0.0174532925199432958);
        static_assert(std::is_floating_point<ValueType>::value || is_fixed_point<ValueType>::value, "ValueType must be a floating|fixed point.");
    public:
        using value_type = ValueType;
        using this_type = radian<ValueType>;

        constexpr radian() noexcept = default;
        constexpr radian(const this_type& other) noexcept
        : angle(other.angle)
        {
        }

        explicit constexpr radian(const ValueType deg) noexcept
        : angle(deg)
        {
        }

        explicit constexpr radian(const degree<ValueType>& deg) noexcept
        : radian(static_cast<ValueType>(deg) * Deg2Rad)
        {
        }

        constexpr this_type& operator=(const this_type& rad) noexcept
        {
            angle = rad.angle;
            return *this;
        }

        explicit constexpr operator ValueType() const
        {
            return angle;
        }

        constexpr this_type operator+(const this_type rad) const
        {
            return this_type(angle + rad.angle);
        }

        constexpr this_type operator-(const this_type rad) const
        {
            return this_type(angle - rad.angle);
        }

        constexpr this_type operator-()
        {
            return this_type(-angle);
        }

        constexpr this_type operator*(const this_type rad) const
        {
            return this_type(angle * rad.angle);
        }

        constexpr this_type operator/(const this_type rad) const
        {
            return this_type(angle / rad.angle);
        }

        constexpr this_type operator*(const ValueType value) const
        {
            return this_type(angle * value);
        }

        constexpr this_type operator/(const ValueType value) const
        {
            return this_type(angle / value);
        }

        constexpr bool operator==(const this_type rad) const
        {
            return is_equal(angle, rad.angle);
        }

        constexpr bool operator==(const degree<ValueType> deg) const
        {
            return is_equal(angle, static_cast<ValueType>(this_type(deg)));
        }

        constexpr bool operator!=(const this_type rad) const
        {
            return !(*this == rad);
        }

        constexpr bool operator!=(const degree<ValueType> deg) const
        {
            return !(*this == deg);
        }

        constexpr bool operator<(const this_type rad) const
        {
            return angle < rad.angle;
        }

        constexpr bool operator>(const this_type rad) const
        {
            return angle > rad.angle;
        }

        constexpr this_type& operator+=(const ValueType val)
        {
            angle += val;
            return *this;
        }

        constexpr this_type& operator+=(const this_type rad)
        {
            angle += rad.angle;
            return *this;
        }

        constexpr this_type& operator-=(const ValueType val)
        {
            angle -= val;
            return *this;
        }

        constexpr this_type& operator-=(const this_type rad)
        {
            angle -= rad.angle;
            return *this;
        }

        constexpr this_type& operator*=(const ValueType val)
        {
            angle *= val;
            return *this;
        }

        constexpr this_type& operator*=(const this_type rad)
        {
            angle *= rad.angle;
            return *this;
        }

        constexpr this_type& operator/=(const ValueType val)
        {
            angle /= val;
            return *this;
        }

        constexpr this_type& operator/=(const this_type rad)
        {
            angle /= rad.angle;
            return *this;
        }

    private:
        ValueType angle = static_cast<ValueType>(0);
    };
} // namespace cml::implementation

#ifdef CML_COMPILE_TEST_CASE

static_assert(cml::implementation::degree<float>(90.0f) == cml::implementation::degree<float>(cml::implementation::radian<float>(cml::implementation::degree<float>(90.0f))));
static_assert(cml::implementation::degree<double>(45.0) == cml::implementation::radian<double>(cml::implementation::degree<double>(45.0)));

#endif
