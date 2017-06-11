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

namespace cml
{
    namespace implementation
    {
        template<typename ValueType>
        struct reference
        {
            constexpr reference() noexcept = default;
            constexpr reference(const reference&) noexcept = default;
            constexpr reference(ValueType* v) noexcept : ptr(v) {};
            constexpr reference &operator = (const reference &o)
            {
                *ptr = *o.ptr;
                return *this;
            }
            constexpr reference &operator = (ValueType o)
            {
                *ptr = o;
                return *this;
            }

            using value_type = ValueType;
            ValueType* ptr = nullptr;

            constexpr operator ValueType& () const noexcept { return *ptr; }

            template<typename Type>
            explicit constexpr operator Type () const noexcept { return static_cast<Type>(*ptr); }

            constexpr reference &operator += (const reference& o) noexcept { *ptr += *o.ptr; return *this; }
            constexpr reference &operator += (const ValueType& o) noexcept { *ptr += o; return *this; }
            constexpr reference &operator -= (const reference& o) noexcept { *ptr -= *o.ptr; return *this; }
            constexpr reference &operator -= (const ValueType& o) noexcept { *ptr -= o; return *this; }
            constexpr reference &operator *= (const reference& o) noexcept { *ptr *= *o.ptr; return *this; }
            constexpr reference &operator *= (const ValueType& o) noexcept { *ptr *= o; return *this; }
            constexpr reference &operator /= (const reference& o) noexcept { *ptr /= *o.ptr; return *this; }
            constexpr reference &operator /= (const ValueType& o) noexcept { *ptr /= o; return *this; }

            constexpr ValueType operator + (const reference& o) const noexcept { return *ptr + *o.ptr; }
            constexpr ValueType operator + (const ValueType& o) const noexcept { return *ptr + o; }
            constexpr ValueType operator - (const reference& o) const noexcept { return *ptr - *o.ptr; }
            constexpr ValueType operator - (const ValueType& o) const noexcept { return *ptr - o; }
            constexpr ValueType operator * (const reference& o) const noexcept { return *ptr * *o.ptr; }
            constexpr ValueType operator * (const ValueType& o) const noexcept { return *ptr * o; }
            constexpr ValueType operator / (const reference& o) const noexcept { return *ptr / *o.ptr; }
            constexpr ValueType operator / (const ValueType& o) const noexcept { return *ptr / o; }
        };

        // traits
        template<typename T> struct is_reference : public std::false_type {};
        template<typename T> struct is_reference<reference<T>> : public std::true_type {};

        template<typename T> struct remove_reference { using type = T; };
        template<typename T> struct remove_reference<reference<T>> : public remove_reference<T> {};

    } // namespace implementation
} // namespace cml
