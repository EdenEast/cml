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

        template<size_t DimX, size_t DimY, typename ValueType> 
        class matrix_components<matrix<DimX, DimY, ValueType>>
        {
            protected:
                struct compiler_marker {};

            public:
                constexpr matrix_components() = default;

                template<typename... Args>
                constexpr matrix_components(ValueType value, Args &&... args)
                    : components {{value, std::forward<Args>(args)...}}
                {
                }

                template<typename... Args>
                constexpr matrix_components(compiler_marker, Args &&... args)
                    : components {matrix<DimX, DimY, ValueType>::template init_components<0>(components, std::forward<Args>(args)...)}
                {
                }

                std::array<ValueType, DimY *DimX> components = {{ ValueType() }};
        };

        template<typename ValueType>
        class matrix_components<matrix<2, 1, ValueType>>
        {
            protected:
                struct compiler_marker {};

            public:
                constexpr matrix_components() = default;

                template<typename... Args>
                constexpr matrix_components(ValueType value, Args &&... args)
                    : components(value, std::forward<Args>(args)...)
                {
                }

                template<typename... Args>
                constexpr matrix_components(compiler_marker, Args &&... args)
                    : components(matrix<2, 1, ValueType>::template init_components<0>(components, std::forward<Args>(args)...))
                {
                }

                union
                {
                    std::array<ValueType, 2> components = {{ ValueType() }};
                    struct { union { ValueType x; ValueType r; ValueType s; }; };
                    struct { union { ValueType y; ValueType g; ValueType t; }; };
                };
        };

        template<typename ValueType>
        class matrix_components<matrix<1, 1, ValueType>>
        {
            protected:
                struct compiler_marker {};

            public:
                constexpr matrix_components() = default;

                template<typename... Args>
                constexpr matrix_components(ValueType value, Args &&... args)
                    : components(value, std::forward<Args>(args)...)
                {
                }

                template<typename... Args>
                constexpr matrix_components(compiler_marker, Args &&... args)
                    : components(matrix<1, 1, ValueType>::template init_components<0>(components, std::forward<Args>(args)...))
                {
                }

                union
                {
                    std::array<ValueType, 1> components = {{ ValueType() }};
                    struct { union { ValueType x; ValueType r; ValueType s; }; };
                    struct { union { ValueType y; ValueType g; ValueType t; }; };
                };
        };

        template<typename ValueType>
        class matrix_components<matrix<3, 1, ValueType>>
        {
            protected:
                struct compiler_marker {};

            public:
                constexpr matrix_components() = default;

                template<typename... Args>
                constexpr matrix_components(ValueType value, Args &&... args)
                    : components(value, std::forward<Args>(args)...)
                {
                }

                template<typename... Args>
                constexpr matrix_components(compiler_marker, Args &&... args)
                    : components(matrix<3, 1, ValueType>::template init_components<0>(components, std::forward<Args>(args)...))
                {
                }

                union
                {
                    std::array<ValueType, 3> components = {{ ValueType() }};
                    struct { union { ValueType x; ValueType r; ValueType s; }; };
                    struct { union { ValueType y; ValueType g; ValueType t; }; };
                    struct { union { ValueType z; ValueType b; ValueType u; }; };
                };
        };

        template<typename ValueType>
        class matrix_components<matrix<4, 1, ValueType>>
        {
            protected:
                struct compiler_marker {};

            public:
                constexpr matrix_components() = default;

                template<typename... Args>
                constexpr matrix_components(ValueType value, Args &&... args)
                    : components {{value, std::forward<Args>(args)...}}
                {
                }

                template<typename... Args>
                constexpr matrix_components(compiler_marker, Args &&... args)
                    : components(matrix<4, 1, ValueType>::template init_components<0>(components, std::forward<Args>(args)...))
                {
                }

                union
                {
                    std::array<ValueType, 4> components = {{ ValueType() }};
                    struct { union { ValueType x; ValueType r; ValueType s; }; };
                    struct { union { ValueType y; ValueType g; ValueType t; }; };
                    struct { union { ValueType z; ValueType b; ValueType u; }; };
                    struct { union { ValueType w; ValueType a; ValueType v; }; };
                };
        };
    }
}
