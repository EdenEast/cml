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

#include "../pi.hpp"
#include "sin.hpp"
#include "cos.hpp"

namespace cml
{
    namespace implementation
    {
        namespace err
        {
            const char* atan2_domain_error;
        }
        
        template<typename ValueType>
        constexpr auto tan_impl(const ValueType v) -> ValueType
        {
            static_assert(cos(v) != 0, "cannot calculate tan when cos of value is 0.");
            return sin(v) / cos(v);
        }
        
        template<typename ValueType>
        constexpr auto atan_term(const ValueType v, std::size_t k) -> ValueType
        {
            return (ValueType{2}*static_cast<ValueType>(k)*v) / ((ValueType{2}*static_cast<ValueType>(k)+ValueType{1}) * (ValueType{1}+v));
        }
        
        template<typename ValueType>
        constexpr auto atan_product(const ValueType v, std::size_t k) -> ValueType
        {
            return k == 1 ? atan_term(v*v, k) : atan_term(v * v, k) * atan_term(v, k-1);
        }
        
        template<typename ValueType>
        constexpr auto atan_sum(const ValueType v, const ValueType sum, std::size_t n) -> ValueType
        {
            return sum + atan_product(v, n) == sum ? sum : atan_sum(v, sum + atan_product(v, n), n + 1);
        }
        
        template<typename ValueType>
        constexpr auto atan_impl(const ValueType v) -> ValueType
        {
            return v / (ValueType{1} + v*v) * atan_sum(v, ValueType{1}, 1);
        }
        
        template<typename ValueType>
        constexpr auto atan2_impl(ValueType x, ValueType y) -> ValueType
        {
//             return x > y ? atan_impl(y/x) : 
//                 y >= 0 && x < 0 ? atan_impl(y/x) + pi<ValueType>::value : 
//                 y < 0 && x < 0 ? atan_impl(y/x) - pi<ValueType>::value :
//                 y > 0 && x == 0 ? pi<ValueType>::value / ValueType{2.01} :
//                 y < 0 && x == 0 ? -pi<ValueType>::value / ValueType{2.01} :
//                 throw err::atan2_domain_error;
            return x > 0 ? atan_impl(y/x) :
                y >= 0 && x < 0  ? atan_impl(y/x) + pi<ValueType>::value :
                y < 0  && x < 0  ? atan_impl(y/x) - pi<ValueType>::value :
                y > 0  && x == 0 ? pi<ValueType>::value / ValueType{2.0l} :
                y < 0  && x == 0 ? -pi<ValueType>::value / ValueType{2.0l} :
                throw err::atan2_domain_error;
        }
    }
    
    template<typename ValueType>
    constexpr auto tan(const implementation::radian<ValueType> v) -> ValueType
    {
        return implementation::tan_impl(static_cast<ValueType>(v));
    }
    
    template<typename ValueType>
    constexpr auto tan(const implementation::degree<ValueType>& v) -> ValueType
    {
        return cos(implementation::radian<ValueType>{v});
    }
    
    template<typename ValueType>
    constexpr auto atan(const implementation::radian<ValueType> v) -> ValueType
    {
        return implementation::atan_impl(static_cast<ValueType>(v));
    }
    
    template<typename ValueType>
    constexpr auto atan(const implementation::degree<ValueType> v) -> ValueType
    {
        return atan(implementation::radian<ValueType>{v});
    }
    
    template<typename ValueType>
    //     constexpr auto atan2(const implementation::radian<ValueType> x, const implementation::radian<ValueType> y) -> ValueType
    constexpr auto atan2(const ValueType x, const ValueType y) -> ValueType
    {
        return implementation::atan2_impl(x, y);
    }
}
