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
#include <type_traits>

namespace cml::implementation
{
    /// @brief What holds the relation component letter -> index
    struct vector_component_index
    {
        const char component;
        const size_t index;
    };

    /// @brief Dictionary for component letter -> index
    static constexpr vector_component_index vector_component_table[] =
    {
        vector_component_index{'x', 0},
        vector_component_index{'y', 1},
        vector_component_index{'z', 2},
        vector_component_index{'w', 3},

        vector_component_index{'r', 0},
        vector_component_index{'g', 1},
        vector_component_index{'b', 2},
        vector_component_index{'a', 3},

        vector_component_index{'s', 0},
        vector_component_index{'t', 1},
        vector_component_index{'u', 2},
        vector_component_index{'v', 3},

        vector_component_index{'0', 0},
        vector_component_index{'1', 1},
        vector_component_index{'2', 2},
        vector_component_index{'3', 3},
        vector_component_index{'4', 4},
        vector_component_index{'5', 5},
        vector_component_index{'6', 6},
        vector_component_index{'7', 7},
        vector_component_index{'8', 8},
        vector_component_index{'9', 9},
    };

    /// @brief Iterates over the table and retrieve the component index
    static constexpr size_t get_vector_component_index(char c)
    {
        for (size_t i = 0; i < std::extent<decltype(vector_component_table)>::value; ++i)
        {
            if (vector_component_table[i].component == c)
                return vector_component_table[i].index;
        }
        return ~0ul;
    }

    /// @brief Vector component index as a type
    template<char Comp, size_t MaxDim = ~0ul>
    struct component_index_t
    {
        static constexpr size_t index = get_vector_component_index(Comp);
        static_assert(index != ~0ul, "Invalid component index: non-defined component index");
        static_assert(index < MaxDim, "Invalid component index: out of range component index");
    };
} // namespace cml::implementation
