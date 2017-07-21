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

#include "definitions.hpp"
#include "matrix_kind.hpp"

namespace cml::implementation
{
    template<size_t DimX, size_t DimY, typename ValueType, matrix_kind Kind> class matrix;
    template<typename ValueType> struct reference;

    /// @brief Return the component count of a given type
    template<typename ValueType>
    struct get_component_count
    {
        static constexpr size_t count = 1;
    };
    template<size_t DimX, size_t DimY, typename ValueType, matrix_kind Kind>
    struct get_component_count<matrix<DimX, DimY, ValueType, Kind>>
    {
        static constexpr size_t count = DimX * DimY;
    };

    /// @brief Count the number of components that are provided in the args
    template<typename... Args>
    struct count_components_from_args
    {
        static constexpr size_t count = 0;
    };
    template<typename ValueType, typename... Args>
    struct count_components_from_args<ValueType, Args...>
    {
        static constexpr size_t count = get_component_count<typename std::remove_reference<typename std::remove_cv<ValueType>::type>::type>::count + count_components_from_args<Args...>::count;
    };

    /// @brief Return the nth component
    template<size_t Index>
    static constexpr auto get_nth_component() -> auto
    {
        static_assert(Index >= 0, "out of range access");
        return; // will cause a compilation error (out of range ?)
    }

    template<size_t Index, typename ValueType, typename... Args>
    static constexpr auto get_nth_component([[maybe_unused]]ValueType&& m, Args&&... args) -> auto;

    template<size_t Index, size_t DimX, size_t DimY, typename ValueType, matrix_kind Kind, typename... Args>
    static constexpr auto get_nth_component_obj([[maybe_unused]]const matrix<DimX, DimY, ValueType, Kind>& m, Args &&... args) -> auto
    {
        if constexpr(Index < DimX * DimY)
            return m.components[Index];
        else
            return get_nth_component<Index - (DimX * DimY)>(std::forward<Args>(args)...);
    }

    template<size_t Index, size_t FB, typename ValueType, typename... Args>
    static constexpr auto get_nth_component_obj([[maybe_unused]]const fixed<ValueType, FB>& m, Args &&... args) -> auto
    {
        if constexpr(Index == 0)
            return m;
        else
            return get_nth_component<Index - 1>(std::forward<Args>(args)...);
    }

    template<size_t Index, typename ValueType, typename... Args>
    static constexpr auto get_nth_component_obj([[maybe_unused]]const reference<ValueType>& m, Args &&... args) -> auto
    {
        if constexpr(Index == 0)
            return m;
        else
            return get_nth_component<Index - 1>(std::forward<Args>(args)...);
    }

    template<size_t Index, typename ValueType, typename... Args>
    static constexpr auto get_nth_component([[maybe_unused]]ValueType&& m, Args&&... args) -> auto
    {
        if constexpr (std::is_arithmetic<typename std::remove_reference<typename std::remove_cv<ValueType>::type>::type>::value || std::is_pointer<ValueType>::value)
        {
            if constexpr(Index == 0)
                return m;
            else
                return get_nth_component<Index - 1>(std::forward<Args>(args)...);
        }
        else
        {
            return get_nth_component_obj<Index>(std::forward<ValueType>(m), std::forward<Args>(args)...);
        }
    }
} // namespace cml::implementation
