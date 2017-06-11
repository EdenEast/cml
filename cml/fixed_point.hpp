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
#include <cstdint>
#include <type_traits>

namespace cml
{
    namespace implementation
    {
        template<size_t Size, bool Signed> struct fixed_type_list {};

        template<> struct fixed_type_list<1, true>
        {
            using type = int8_t;
            using next = fixed_type_list<2, true>;
        };
        template<> struct fixed_type_list<2, true>
        {
            using type = int16_t;
            using next = fixed_type_list<4, true>;
        };
        template<> struct fixed_type_list<4, true>
        {
            using type = int32_t;
            using next = fixed_type_list<8, true>;
        };
        template<> struct fixed_type_list<8, true>
        {
            using type = int64_t;
            using next = fixed_type_list<8, true>; // no more :(
        };
        template<> struct fixed_type_list<1, false>
        {
            using type = uint8_t;
            using next = fixed_type_list<2, false>;
        };
        template<> struct fixed_type_list<2, false>
        {
            using type = uint16_t;
            using next = fixed_type_list<4, false>;
        };
        template<> struct fixed_type_list<4, false>
        {
            using type = uint32_t;
            using next = fixed_type_list<8, false>;
        };
        template<> struct fixed_type_list<8, false>
        {
            using type = uint64_t;
            using next = fixed_type_list<8, false>; // no more :(
        };
    } // namespace implementation

    /// @brief As float is a floating point, fixed is a fixed point
    template<typename Type, size_t FractionnalBits = sizeof(Type) * 8 / 2>
    struct fixed
    {
        static_assert(std::is_integral<Type>::value, "fixed point base type needs to be an integral type");
        static_assert(!(FractionnalBits % 2), "the fractional part MUST be a multiple of 2");
        static_assert(FractionnalBits < sizeof(Type) * 8, "the fractional part MUST be lower than the number of bit the underlying type has");

        static constexpr struct from_fixed_t {} from_fixed = from_fixed_t{};
        static constexpr bool is_signed = std::is_signed<Type>::value;
        using value_type = Type;
        using upper_type = typename implementation::fixed_type_list<sizeof(Type), is_signed>::next::type;

        static constexpr size_t fractional_bits = FractionnalBits;
        static constexpr size_t integer_bits = sizeof(Type) * 8 - FractionnalBits;
        static_assert(is_signed && FractionnalBits < (sizeof(Type) * 8 - 1), "fixed point number have a signed format yet cannot have a sign (the fractional part span across all the availlable bits)");


        constexpr fixed() noexcept = default;
        constexpr fixed(const fixed&) noexcept = default;
        constexpr fixed& operator = (const fixed&) noexcept = default;

        template<typename ConvType>
        constexpr fixed(ConvType value) noexcept
        : data(from(value).data)
        {
        }

        /// @brief Force no conversion
        constexpr fixed(from_fixed_t, Type value) noexcept
        : data(value)
        {
        }

        template<typename ConvType>
        constexpr fixed& operator = (ConvType o) noexcept
        {
            data = convert(o).data;
        }


        Type data = 0;

        /// @brief Convert any integral/floating point type into a fixed point
        template<typename ConvType>
        static constexpr fixed from(ConvType x) noexcept
        {
            if constexpr (std::is_arithmetic<ConvType>::value)
                return {from_fixed, static_cast<Type>(static_cast<ConvType>(x) * static_cast<ConvType>(1ul << FractionnalBits))};
            else
                return convert(x);
        }

        /// @brief Convert any other fixed point type into a given fixed point
        template<typename Other, size_t Frac>
        static constexpr fixed convert(const fixed<Other, Frac>& o)
        {
            if constexpr(Frac > FractionnalBits)
                return {from_fixed, static_cast<Type>(o.data >> (Frac - FractionnalBits))};
            else if constexpr (Frac < FractionnalBits)
                return {from_fixed, static_cast<Type>(o.data) << (FractionnalBits - Frac)};
            else
                return {from_fixed, static_cast<Type>(o.data)};
        }

        /// @brief Convert a fixed point to any given type
        template<typename ConvType>
        constexpr ConvType to() const noexcept
        {
            if constexpr(std::is_arithmetic<ConvType>::value)
                return static_cast<ConvType>(data) / static_cast<ConvType>(1ul << FractionnalBits);
            else
                return ConvType::convert(*this);
        }

        /// @brief Allow static cast to work for conversion to arythmetic numbers / other fixed point formats
        template<typename ConvType>
        explicit constexpr operator ConvType() const
        {
            return to<ConvType>();
        }

        constexpr fixed& operator ++ () noexcept { data += static_cast<Type>(1) << FractionnalBits; return *this; }
        constexpr fixed& operator ++ (int) noexcept { data += static_cast<Type>(1) << FractionnalBits; return *this; }
        constexpr fixed& operator -- () noexcept { data -= static_cast<Type>(1) << FractionnalBits; return *this; }
        constexpr fixed& operator -- (int) noexcept { data -= static_cast<Type>(1) << FractionnalBits; return *this; }

        constexpr fixed& operator += (const fixed o) noexcept { data += o.data; return *this; }
        constexpr fixed& operator -= (const fixed o) noexcept { data -= o.data; return *this; }
        constexpr fixed& operator *= (const fixed o) noexcept { data = static_cast<Type>((static_cast<upper_type>(data) * static_cast<upper_type>(o.data)) >> FractionnalBits); return *this; }
        constexpr fixed& operator /= (const fixed o) noexcept { data = static_cast<Type>((static_cast<upper_type>(data) << FractionnalBits) / o.data); return *this; }

        constexpr fixed& operator <<= (size_t o) noexcept { data <<= o; return *this; }
        constexpr fixed& operator >>= (size_t o) noexcept { data >>= o; }

        constexpr auto operator - () const noexcept -> auto
        {
            if constexpr(is_signed)
            {
                return fixed {from_fixed, static_cast<Type>(-data)};
            }
            else
            {
                static_assert(FractionnalBits < (sizeof(Type) * 8 - 1), "cannot negate fixed point number: there is no possibility to have a sign in the given format");
                using dest_type = typename implementation::fixed_type_list<sizeof(Type), true>::type;
                return fixed<dest_type, FractionnalBits>{fixed<dest_type, FractionnalBits>::from_fixed, -static_cast<dest_type>(data)};
            }
        }

        constexpr fixed operator + (const fixed o) const noexcept { return {from_fixed, static_cast<Type>(data + o.data)}; }
        constexpr fixed operator - (const fixed o) const noexcept { return {from_fixed, static_cast<Type>(data - o.data)}; }
        constexpr fixed operator * (const fixed o) const noexcept { return {from_fixed, static_cast<Type>((static_cast<upper_type>(data) * static_cast<upper_type>(o.data)) >> FractionnalBits)}; }
        constexpr fixed operator / (const fixed o) const noexcept { return {from_fixed, static_cast<Type>((static_cast<upper_type>(data) << FractionnalBits) / o.data)}; }

        constexpr fixed operator << (size_t o) const noexcept { return {from_fixed, data << o}; }
        constexpr fixed operator >> (size_t o) const noexcept { return {from_fixed, data >> o}; }

        constexpr bool operator == (const fixed o) const noexcept { return data == o.data; }
        constexpr bool operator != (const fixed o) const noexcept { return data != o.data; }
        constexpr bool operator >= (const fixed o) const noexcept { return data >= o.data; }
        constexpr bool operator <= (const fixed o) const noexcept { return data <= o.data; }
        constexpr bool operator > (const fixed o) const noexcept { return data > o.data; }
        constexpr bool operator < (const fixed o) const noexcept { return data < o.data; }
    };
} // namespace cml
