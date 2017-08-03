//
// Copyright (c) 2017 James Simpson, Timoth�e Feuillet
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

namespace cml
{
    template<typename ValueType>
    constexpr ValueType abs(ValueType v)
    {
        return v < ValueType{0} ? -v : v;
    }
}

#ifdef CML_COMPILE_TEST_CASE

static_assert(cml::abs( 1) == 1);
static_assert(cml::abs(-1) == 1);
static_assert(cml::abs(-0) == 0);

static_assert(cml::abs( 1.f) == 1.f);
static_assert(cml::abs(-1.f) == 1.f);
static_assert(cml::abs( 1.0) == 1.0);
static_assert(cml::abs(-1.0) == 1.0);
static_assert(cml::abs( 1.l) == 1.l);
static_assert(cml::abs(-1.l) == 1.l);

#endif
