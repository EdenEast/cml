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

#include <type_traits>
#include <utility>

#include "../traits.hpp"

namespace cml
{
    template<typename ValueType1, typename ValueType2, typename... Args>
    constexpr auto min(const ValueType1& v1, const ValueType2& v2, Args&&... args) -> auto;
    template<typename ValueType> constexpr ValueType min(const ValueType& v);

    namespace implementation
    {
        /// \brief Matrix / Scalar
        template<typename MatrixType, typename ScalarType, typename... Args, size_t... Idxs>
        constexpr auto ms_min(std::index_sequence<Idxs...>, const MatrixType& v1, const ScalarType& v2, Args&&... args) -> auto
        {
            return min(MatrixType{min(v1.components[Idxs], v2)...}, std::forward<Args>(args)...);
        }

        /// \brief Matrix / Matrix min
        template<typename MatrixType, typename... Args, size_t... Idxs>
        constexpr auto mm_min(std::index_sequence<Idxs...>, const MatrixType& v1, const MatrixType& v2, Args&&... args) -> auto
        {
            return min(MatrixType{min(v1.components[Idxs], v2.components[Idxs])...}, std::forward<Args>(args)...);
        }
    } // namespace implementation

    template<typename ValueType>
    constexpr ValueType min(const ValueType& v)
    {
        return v;
    }

    template<typename ValueType1, typename ValueType2, typename... Args>
    constexpr auto min(const ValueType1& v1, const ValueType2& v2, Args&&... args) -> auto
    {
        // lazy-man SFINAE / function deduction
        if constexpr(is_matrix<ValueType1>::value)
        {
            if constexpr(std::is_same<ValueType1, ValueType2>::value)
                return implementation::mm_min(std::make_index_sequence<matrix_traits<ValueType1>::components>{}, v1, v2, std::forward<Args>(args)...);
            else if constexpr(!is_matrix<ValueType2>::value)
                return implementation::ms_min(std::make_index_sequence<matrix_traits<ValueType1>::components>{}, v1, v2, std::forward<Args>(args)...);
            else
                static_assert(is_matrix<ValueType2>::value, "only min(matrix, matrix) [where both matrices are the same size] are allowed !");
        }
        else if constexpr(is_matrix<ValueType2>::value)
        {
            return implementation::ms_min(std::make_index_sequence<matrix_traits<ValueType2>::components>{}, v2, v1, std::forward<Args>(args)...);
        }
        else
        {
            // everything else
            return min(v1 < v2 ? v1 : v2, std::forward<Args>(args)...);
        }
    }
}

#ifdef CML_COMPILE_TEST_CASE

static_assert(cml::min(1, 2) == 1);
static_assert(cml::min(5, -1, 2) == -1);
static_assert(cml::min(1, 2, -1) == -1);
static_assert(cml::min(2, 2, 2) == 2);
static_assert(cml::min(2.0, 1.0) == 1.0);
static_assert(cml::min(cml::f1616{1.0}, cml::f1616{2.0}) == cml::f1616{1.0});

static_assert(cml::min(cml::f1616vec2{1.0, 2.0}, cml::f1616{0.5}) == cml::f1616vec2{0.5, 0.5});
static_assert(cml::min(cml::f1616{1.0}, cml::f1616{2.0}, cml::f1616vec2{1.0, 2.0}, cml::f1616{0.5}) == cml::f1616vec2{0.5, 0.5});
static_assert(cml::min(cml::f1616{1.0}, cml::f1616{2.0}, cml::f1616{0.5}, cml::f1616vec2{1.0, 2.0}) == cml::f1616vec2{0.5, 0.5});
static_assert(cml::min(8.0, 2.0, 4.0, cml::dmat2{1.0, 2.0, 8.0, 1.5}) == cml::dmat2{1.0, 2.0, 2.0, 1.5});

#endif /*CML_COMPILE_TEST_CASE*/


