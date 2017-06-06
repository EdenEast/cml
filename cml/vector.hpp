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

#include <array>
#include <cstddef>
#include <type_traits>

#include "vector_component_table.hpp"

namespace cml
{
    namespace implementation
    {
        template<size_t Dim, typename ValueType> class vector;
        template<typename ValueType, size_t Count> struct vector_at_return_type { using type = vector<Count, ValueType>; };
        template<typename ValueType> struct vector_at_return_type<ValueType, 1> { using type = ValueType &; };
        template<typename ValueType> struct vector_at_return_type<ValueType, 0> { using type = void; };

        /// @brief Generic vector class. Can hold multiple values of *any* type
        /// @tparam Dim The number of component this vector have
        /// @tparam ValueType the type of vector's components
        template<size_t Dim, typename ValueType>
        class vector
        {
            private: // a bunch of static asserts:
                static_assert(Dim > 1, "cml::vector dimension (Dim template parameter) must not be 0 nor 1");
                static_assert(std::is_default_constructible<ValueType>::value, "cml::vector ValueType must be default constructible");
                static_assert(std::is_copy_assignable<ValueType>::value, "cml::vector ValueType must be copy assignable");
                static_assert(std::is_copy_constructible<ValueType>::value, "cml::vector ValueType must be copy constructible");

            private: // type helpers:
                struct marker_type {};

            public:
                // defaulted copy, assignation, ...
                constexpr vector() noexcept = default;
                constexpr vector(const vector&) noexcept = default;
                constexpr vector& operator = (const vector&) noexcept = default;
                ~vector() noexcept = default;

                template<typename... Types>
                constexpr vector(Types &&... values) noexcept
                : components{{values...}}
                {
                }

                /// @brief Multi component access using large char at<'xyy'>() will return a three component vector
                template<unsigned int Components>
                constexpr auto at() -> typename vector_at_return_type<ValueType, (Components > 0x000000FFu ? 2 : (Components > 0 ? 1 : 0))>::type
                {
                    if constexpr (Components == 0)
                        return; // void
                    else if constexpr (Components <= 0xFFu)
                        return components[component_index_t<static_cast<char>(Components), Dim>::index];
                    else if constexpr (Components <= 0xFFFFu)
                        return at_separate<static_cast<char>((Components >> 8) & 0xFF), static_cast<char>((Components >> 0) & 0xFF)>();
                    else if constexpr (Components <= 0xFFFFFFu)
                        return at_separate<static_cast<char>((Components >> 16) & 0xFF), static_cast<char>((Components >> 8) & 0xFF), static_cast<char>((Components >> 0) & 0xFF)>();
                    else
                        return at_separate<static_cast<char>((Components >> 24) & 0xFF), static_cast<char>((Components >> 16) & 0xFF), static_cast<char>((Components >> 8) & 0xFF), static_cast<char>((Components >> 0) & 0xFF)>();
                }

                /// @brief Component Access (at<'x'>() will be the X component, at<'x', 'y'>() will return a vector of the two component X and Y
                template<char... Components>
                constexpr auto at_separate() -> typename vector_at_return_type<ValueType, sizeof...(Components)>::type
                {
                    if constexpr (sizeof...(Components) == 0)
                        return; // void
                    else if constexpr (sizeof...(Components) == 1)
                        return components[component_index_t<Components..., Dim>::index];
                    else
                        return vector<sizeof...(Components), ValueType>({components[component_index_t<Components, Dim>::index]...});
                }

            private: // helpers
            private:
                std::array<ValueType, Dim> components = {ValueType()};
        };
    } // namespace implementation
} // namespace cml

