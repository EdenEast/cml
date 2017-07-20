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
#include "matrix.hpp"

namespace cml::implementation
{
    template<typename ValueType>
    class quaternion : public matrix<4, 1, ValueType, matrix_kind::quaternion>
    {
    public:
        using matrix<4, 1, ValueType, matrix_kind::quaternion>::matrix;
        constexpr quaternion() noexcept : quaternion(0, 0, 0, 1) {}
        static constexpr quaternion<ValueType> identity() { return quaternion<ValueType>(0, 0, 0, 1); }
    };
} // namespace cml::implementation

#ifdef CML_COMPILE_TEST_CASE

static_assert(cml::implementation::quaternion<float>() == cml::implementation::matrix<4, 1, float, cml::implementation::matrix_kind::quaternion>(0, 0, 0, 1));

#endif
