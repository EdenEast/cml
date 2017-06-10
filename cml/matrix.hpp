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

#include "matrix_components.hpp"
#include "vector_component_table.hpp"

namespace cml
{
    namespace implementation
    {
        template<size_t DimX, size_t DimY, typename ValueType> class matrix;
        template<typename ValueType, size_t DimX, size_t DimY> struct matrix_at_return_type { using type = matrix<DimX, DimY, ValueType>; };
        template<typename ValueType> struct matrix_at_return_type<ValueType, 1, 1> { using type = ValueType &; };
        template<typename ValueType> struct matrix_at_return_type<ValueType, 0, 1> { using type = void; };

        /// @brief Generic matrix class. Can hold multiple values of *any* type
        /// @tparam Dim The number of component this matrix have
        /// @tparam ValueType the type of matrix's components
        template<size_t DimX, size_t DimY, typename ValueType>
        class matrix : public matrix_components<matrix<DimX, DimY, ValueType>>
        {
            private: // a bunch of static asserts:
                static_assert(DimX * DimY > 0, "cml::matrix dimensions (Dim{X, Y} template parameters) must not be 0");
                static_assert(std::is_default_constructible<ValueType>::value, "cml::matrix ValueType must be default constructible");
                static_assert(std::is_copy_assignable<ValueType>::value, "cml::matrix ValueType must be copy assignable");
                static_assert(std::is_copy_constructible<ValueType>::value, "cml::matrix ValueType must be copy constructible");

            public:
                // defaulted copy, assignation, ...
                constexpr matrix() noexcept = default;
                constexpr matrix(const matrix&) noexcept = default;
                constexpr matrix& operator = (const matrix&) noexcept = default;
                ~matrix() noexcept = default;

                constexpr matrix &operator = (ValueType value) noexcept
                {
                    assign_value_type(std::make_index_sequence<DimX * DimY>{}, value);
                    return *this;
                }

                explicit constexpr matrix(ValueType value) noexcept
                : matrix(std::make_index_sequence<DimX * DimY>{}, value)
                {
                }

                explicit constexpr matrix(const std::array<ValueType, DimX * DimY>& value) noexcept
                : matrix_components<matrix<DimX, DimY, ValueType>>(value)
                {
                }

                /// @brief Generic construction from either values and matrices (in any position)
                template<typename Type2, typename... Types>
                constexpr matrix(ValueType v1, Type2 v2, Types &&... values) noexcept
                : matrix_components<matrix<DimX, DimY, ValueType>>(std::forward<ValueType>(v1), std::forward<Type2>(v2), std::forward<Types>(values)...)
                {
                }

                /// @brief Generic construction from either values and vectors (in any position)
                template<typename Type1, size_t D1, size_t D2, typename Type2, typename... Types>
                constexpr matrix(matrix<D1, D2, Type1>&& v1, Type2 v2, Types &&... values) noexcept
                : matrix_components<matrix<DimX, DimY, ValueType>>(std::forward<matrix<D1, D2, Type1>>(v1), std::forward<Type2>(v2), std::forward<Types>(values)...)
                {
                }

                static constexpr matrix<DimX, DimY, ValueType> identity()
                {
                    static_assert(DimX == DimY, "Only square matrices can be identity matrices");
                    return make_identity(std::make_index_sequence<DimX>{});
                }

                /// @brief Cast the matrix to any integral type that has the same size (or bigger)
                template<typename Type>
                explicit constexpr operator Type() const
                {
                    static_assert(std::is_integral<Type>::value); // mostly for SFINAE
                    static_assert(sizeof(Type) >= sizeof(ValueType) * DimX * DimY); // mostly for SFINAE
                    return convert_to_type<Type>(std::make_index_sequence<DimX * DimY>{});
                }

                /// @brief Safly cast to a matrix /... that has a type that will @b not loose any information
                template<typename Type>
                constexpr operator matrix<DimX, DimY, Type>() const
                {
                    static_assert(std::is_same<Type, typename std::common_type<Type, ValueType>::type>::value, "casting to another matrix with precision loss is forbidden"); // mostly for SFINAE
                    return convert_to_matrix<Type>(std::make_index_sequence<DimX * DimY>{});
                }

                /// @brief Unsafly cast to a matrix /... that has a type that will loose some information
                template<typename Type>
                constexpr matrix<DimX, DimY, Type> unsafe_cast() const
                {
                    return convert_to_matrix<Type>(std::make_index_sequence<DimX * DimY>{});
                }

                /// @brief Multi component access using large char at<'xyy'>() will return a three component matrix
                template<unsigned int Components>
                constexpr auto _() -> typename matrix_at_return_type<ValueType, (Components > 0x000000FFu ? 2 : (Components > 0 ? 1 : 0)), 1>::type
                {
                    if constexpr (Components == 0)
                        return; // void
                    else if constexpr (Components <= 0xFFu)
                        return this->components[component_index_t<static_cast<char>(Components), DimX * DimY>::index];
                    else if constexpr (Components <= 0xFFFFu)
                        return at_separate<static_cast<char>((Components >> 8) & 0xFF), static_cast<char>((Components >> 0) & 0xFF)>();
                    else if constexpr (Components <= 0xFFFFFFu)
                        return at_separate<static_cast<char>((Components >> 16) & 0xFF), static_cast<char>((Components >> 8) & 0xFF), static_cast<char>((Components >> 0) & 0xFF)>();
                    else
                        return at_separate<static_cast<char>((Components >> 24) & 0xFF), static_cast<char>((Components >> 16) & 0xFF), static_cast<char>((Components >> 8) & 0xFF), static_cast<char>((Components >> 0) & 0xFF)>();
                }

                /// @brief Multi component access using large char at<'xyy'>() will return a three component matrix
                template<unsigned int Components>
                constexpr auto _() const -> const typename matrix_at_return_type<ValueType, (Components > 0x000000FFu ? 2 : (Components > 0 ? 1 : 0)), 1>::type
                {
                    if constexpr (Components == 0)
                        return; // void
                    else if constexpr (Components <= 0xFFu)
                        return this->components[component_index_t<static_cast<char>(Components), DimX * DimY>::index];
                    else if constexpr (Components <= 0xFFFFu)
                        return at_separate<static_cast<char>((Components >> 8) & 0xFF), static_cast<char>((Components >> 0) & 0xFF)>();
                    else if constexpr (Components <= 0xFFFFFFu)
                        return at_separate<static_cast<char>((Components >> 16) & 0xFF), static_cast<char>((Components >> 8) & 0xFF), static_cast<char>((Components >> 0) & 0xFF)>();
                    else
                        return at_separate<static_cast<char>((Components >> 24) & 0xFF), static_cast<char>((Components >> 16) & 0xFF), static_cast<char>((Components >> 8) & 0xFF), static_cast<char>((Components >> 0) & 0xFF)>();
                }

                /// @brief Component Access (at<'x'>() will be the X component, at<'x', 'y'>() will return a matrix of the two component X and Y
                template<char... Components>
                constexpr auto at_separate() -> typename matrix_at_return_type<ValueType, sizeof...(Components), 1>::type
                {
                    if constexpr (sizeof...(Components) == 0)
                        return; // void
                    else if constexpr (sizeof...(Components) == 1)
                        return this->components[component_index_t<Components..., DimX * DimY>::index];
                    else
                        return matrix<sizeof...(Components), 1, ValueType>(this->components[component_index_t<Components, DimX * DimY>::index]...);
                }

                /// @brief Component Access (at<'x'>() will be the X component, at<'x', 'y'>() will return a matrix of the two component X and Y
                template<char... Components>
                constexpr auto at_separate() const -> const typename matrix_at_return_type<ValueType, sizeof...(Components), 1>::type
                {
                    if constexpr (sizeof...(Components) == 0)
                        return; // void
                    else if constexpr (sizeof...(Components) == 1)
                        return this->components[component_index_t<Components..., DimX * DimY>::index];
                    else
                        return matrix<sizeof...(Components), 1, ValueType>(this->components[component_index_t<Components, DimX * DimY>::index]...);
                }

            private: // helpers
                template<size_t... Idxs>
                constexpr matrix(std::index_sequence<Idxs...>, ValueType vt)
                : matrix_components<matrix<DimX, DimY, ValueType>>{((void)Idxs, vt)...}
                {}

                template<size_t... Idxs>
                static constexpr matrix make_identity(std::index_sequence<Idxs...>)
                {
                    return matrix(make_identity_row<Idxs>(std::make_index_sequence<DimY>{})...);
                }
                template<size_t X, size_t... Idxs>
                static constexpr matrix<DimX, 1, ValueType> make_identity_row(std::index_sequence<Idxs...>)
                {
                    return matrix<DimX, 1, ValueType>((Idxs == X ? ValueType(1) : ValueType(0))...);
                }

                template<size_t... Idxs>
                constexpr void assign_value_type(std::index_sequence<Idxs...>, ValueType vt)
                {
#ifndef _MSC_VER
                    ((this->components[Idxs] = vt), ...);
#else
                    using ar_t = int[];
                    (void)(ar_t{((this->components[Idxs] = vt), 0)...});
#endif
                }

                template<typename Type, size_t... Idxs>
                constexpr Type convert_to_type(std::index_sequence<Idxs...>) const
                {
#ifndef _MSC_VER
                    return ((Type(this->components[Idxs]) << (Idxs * sizeof(ValueType) * 8)) | ...);
#else
                    Type ret = 0;
                    using ar_t = int[];
                    (void)(ar_t{((ret |= Type(this->components[Idxs]) << (Idxs * sizeof(ValueType) * 8)), 0)...});
                    return ret;
#endif
                }
                template<typename Type, size_t... Idxs>
                constexpr matrix<DimX, DimY, Type> convert_to_matrix(std::index_sequence<Idxs...>) const
                {
                    return matrix<DimX, DimY, Type>(Type(this->components[Idxs])...);
                }

            public: // should be internal
                // stored as | [ [X, Y, Z],
                //           |   [X, Y, Z],
                //           v   [X, Y, Z] ]
                //         DimY  --------> DimX
                //std::array<ValueType, DimY * DimX> components = {{ValueType()}};
        };
    } // namespace implementation
} // namespace cml
