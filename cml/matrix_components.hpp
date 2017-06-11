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

#include "definitions.hpp"
#include "matrix_initializer.hpp"

namespace cml
{
    namespace implementation
    {
        template<size_t DimX, size_t DimY, typename ValueType> class matrix;

        // stored as | [ [X, Y, Z],
        //           |   [X, Y, Z],
        //           v   [X, Y, Z] ]
        //         DimY  --------> DimX
        template<typename Child> class matrix_components {};

#define CML_MATRIX_COMPONENTS_BODY(x, y, m) \
            protected: \
                constexpr matrix_components() noexcept : components{{ValueType()}} {} \
                constexpr matrix_components(const matrix_components&o) noexcept : components{{o.components}} {} \
                constexpr matrix_components& operator = (const matrix_components&o) noexcept { components = o.components; return *this; } \
 \
                constexpr matrix_components(const std::array<ValueType, x * y>& ar) noexcept : components {ar} {} \
 \
                template<typename... Args> \
                constexpr matrix_components(Args &&... args) noexcept \
                : matrix_components(std::make_index_sequence<count_components_from_args<Args...>::count>{}, std::forward<Args>(args)...) \
                {} \
 \
            private: \
                template<size_t... Idxs, typename... Args> \
                constexpr matrix_components(std::index_sequence<Idxs...>, Args &&... args) noexcept \
                : components {{static_cast<ValueType>(get_nth_component<Idxs>(std::forward<Args>(args)...))...}} \
                {} \
 \
            public:

        // scalar:
        template<typename ValueType>
        class matrix_components<matrix<1, 1, ValueType>>
        {
            private:
                using matrix_t = matrix<1, 1, ValueType>;
                CML_MATRIX_COMPONENTS_BODY(1, 1, matrix_t)

            public:
                union
                {
                    std::array<ValueType, 1> components = {{ ValueType() }};
                    union { ValueType x; ValueType r; ValueType s; };
                };
        };

        // vectors:

        template<typename ValueType>
        class matrix_components<matrix<2, 1, ValueType>>
        {
            private:
                using matrix_t = matrix<2, 1, ValueType>;
                CML_MATRIX_COMPONENTS_BODY(2, 1, matrix_t)

            public:
                union
                {
                    std::array<ValueType, 2> components = {{ ValueType() }};
                    struct
                    {
                        union { ValueType x; ValueType r; ValueType s; };
                        union { ValueType y; ValueType g; ValueType t; };
                    };
                };
        };
        template<typename ValueType>
        class matrix_components<matrix<1, 2, ValueType>>
        {
            private:
                using matrix_t = matrix<1, 2, ValueType>;
                CML_MATRIX_COMPONENTS_BODY(1, 2, matrix_t)

            public:
                union
                {
                    std::array<ValueType, 2> components = {{ ValueType() }};
                    struct
                    {
                        union { ValueType x; ValueType r; ValueType s; };
                        union { ValueType y; ValueType g; ValueType t; };
                    };
                };
        };

        template<typename ValueType>
        class matrix_components<matrix<3, 1, ValueType>>
        {
            private:
                using matrix_t = matrix<3, 1, ValueType>;
                CML_MATRIX_COMPONENTS_BODY(3, 1, matrix_t)

            public:
                union
                {
                    std::array<ValueType, 3> components = {{ ValueType() }};
                    struct
                    {
                        union { ValueType x; ValueType r; ValueType s; };
                        union { ValueType y; ValueType g; ValueType t; };
                        union { ValueType z; ValueType b; ValueType u; };
                    };
                };
        };
        template<typename ValueType>
        class matrix_components<matrix<1, 3, ValueType>>
        {
            private:
                using matrix_t = matrix<1, 3, ValueType>;
                CML_MATRIX_COMPONENTS_BODY(1, 3, matrix_t)

            public:
                union
                {
                    std::array<ValueType, 3> components = {{ ValueType() }};
                    struct
                    {
                        union { ValueType x; ValueType r; ValueType s; };
                        union { ValueType y; ValueType g; ValueType t; };
                        union { ValueType z; ValueType b; ValueType u; };
                    };
                };
        };

        template<typename ValueType>
        class matrix_components<matrix<4, 1, ValueType>>
        {
            private:
                using matrix_t = matrix<4, 1, ValueType>;
                CML_MATRIX_COMPONENTS_BODY(4, 1, matrix_t)

            public:
                union
                {
                    std::array<ValueType, 4> components = {{ ValueType() }};
                    struct
                    {
                        union { ValueType x; ValueType r; ValueType s; };
                        union { ValueType y; ValueType g; ValueType t; };
                        union { ValueType z; ValueType b; ValueType u; };
                        union { ValueType w; ValueType a; ValueType v; };
                    };
                };
        };

        template<typename ValueType>
        class matrix_components<matrix<1, 4, ValueType>>
        {
            private:
                using matrix_t = matrix<1, 4, ValueType>;
                CML_MATRIX_COMPONENTS_BODY(1, 4, matrix_t)

            public:
                union
                {
                    std::array<ValueType, 4> components = {{ ValueType() }};
                    struct
                    {
                        union { ValueType x; ValueType r; ValueType s; };
                        union { ValueType y; ValueType g; ValueType t; };
                        union { ValueType z; ValueType b; ValueType u; };
                        union { ValueType w; ValueType a; ValueType v; };
                    };
                };
        };

        template<size_t DimX, typename ValueType>
        class matrix_components<matrix<DimX, 1, ValueType>>
        {
            private:
                using matrix_t = matrix<DimX, 1, ValueType>;
                CML_MATRIX_COMPONENTS_BODY(DimX, 1, matrix_t)

            public:
                union
                {
                    std::array<ValueType, DimX> components = {{ ValueType() }};
                    struct
                    {
                        union { ValueType x; ValueType r; ValueType s; };
                        union { ValueType y; ValueType g; ValueType t; };
                        union { ValueType z; ValueType b; ValueType u; };
                        union { ValueType w; ValueType a; ValueType v; };
                    };
                };
        };

        template<size_t DimY, typename ValueType>
        class matrix_components<matrix<1, DimY, ValueType>>
        {
            private:
                using matrix_t = matrix<1, DimY, ValueType>;
                CML_MATRIX_COMPONENTS_BODY(1, DimY, matrix_t)

            public:
                union
                {
                    std::array<ValueType, DimY> components = {{ ValueType() }};
                    struct
                    {
                        union { ValueType x; ValueType r; ValueType s; };
                        union { ValueType y; ValueType g; ValueType t; };
                        union { ValueType z; ValueType b; ValueType u; };
                        union { ValueType w; ValueType a; ValueType v; };
                    };
                };
        };

        // matrices (somewhat generic)
        template<size_t DimX, size_t DimY, typename ValueType>
        class matrix_components<matrix<DimY, DimX, ValueType>>
        {
            private:
                static_assert(DimY > 1);
                static_assert(DimX > 1); // only matches matrices
                using matrix_t = matrix<DimX, DimY, ValueType>;
                CML_MATRIX_COMPONENTS_BODY(DimX, DimY, matrix_t)

            public:
                union
                {
                    std::array<ValueType, DimX * DimY> components = {{ ValueType() }};
                    std::array<matrix<DimX, 1, ValueType>, DimY> rows;
                };
        };

#undef CML_MATRIX_COMPONENTS_BODY
    }
}
