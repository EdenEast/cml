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
#include "matrix.hpp"
#include "fixed_point.hpp"
#include "reference.hpp"

namespace cml::implementation
{
#ifdef _MSC_VER
    using ar_t = int[];
#endif

    // matrix - matrix operations

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_mm_add(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
        return {v1.components[Idxs] + v2.components[Idxs]...};
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_mm_sub(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
        return {v1.components[Idxs] - v2.components[Idxs]...};
    }

    template<size_t Idx, typename VType, size_t DimX1, size_t DimY1, size_t DimX2, size_t DimY2, matrix_kind Kind, size_t... Idxs, size_t... CommonIdxs>
    static constexpr VType matrix_mm_mul_dot(std::index_sequence<CommonIdxs...>, const matrix<DimX1, DimY1, VType, Kind>& v1, const matrix<DimX2, DimY2, VType, Kind>& v2)
    {
        constexpr size_t x = Idx % DimX2;
        constexpr size_t y = Idx / DimX2;

#ifndef _MSC_VER
        return ((v1.components[CommonIdxs + y * DimX1] * v2.components[x + CommonIdxs * DimX2]) + ...);
#else
        VType ret = VType(0);
        (void)(ar_t {((ret += v1.components[CommonIdxs + y * DimX1] * v2.components[x + CommonIdxs * DimX2]), 0)...});
        return ret;
#endif
    }

    template<typename VType, size_t DimX1, size_t DimY1, size_t DimX2, size_t DimY2, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX2, DimY1, typename remove_reference<VType>::type, Kind> matrix_mm_mul(std::index_sequence<Idxs...>, const matrix<DimX1, DimY1, VType, Kind>& v1, const matrix<DimX2, DimY2, VType, Kind>& v2)
    {
        return
        {
            matrix_mm_mul_dot<Idxs>(std::make_index_sequence<DimY2>{}, v1, v2)...
        };
    }
    template<typename VType, size_t DimX1, size_t DimY1, size_t DimX2, size_t DimY2, matrix_kind Kind>
    constexpr auto matrix_mm_mul(const matrix<DimX1, DimY1, VType, Kind>& v1, const matrix<DimX2, DimY2, VType, Kind>& v2) -> auto
    {
        static_assert(DimX1 == DimY2, "Cannot multiply matrices when the number of columns of the first matrix is different from the number of rows of the second matrix");
        return matrix_mm_mul(std::make_index_sequence<DimX2 * DimY1>{}, v1, v2);
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_mm_div(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
        return {v1.components[Idxs] / v2.components[Idxs]...};
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr bool matrix_mm_eq(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
#ifndef _MSC_VER
        return ((v1.components[Idxs] == v2.components[Idxs]) && ...);
#else
        bool ret = true;
        (void)(ar_t{((ret = ret && v1.components[Idxs] == v2.components[Idxs]), 0)...});
        return ret;
#endif
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr bool matrix_mm_neq(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
#ifndef _MSC_VER
        return ((v1.components[Idxs] != v2.components[Idxs]) && ...);
#else
        bool ret = true;
        (void)(ar_t{((ret = ret && v1.components[Idxs] != v2.components[Idxs]), 0)...});
        return ret;
#endif
    }

    // matrix - scalar operations

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs, typename SType>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_ms_add(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, SType v2)
    {
        return {v1.components[Idxs] + v2...};
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs, typename SType>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_ms_sub(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, SType v2)
    {
        return {v1.components[Idxs] - v2...};
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs, typename SType>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_ms_mul(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, SType v2)
    {
        return {v1.components[Idxs] * v2...};
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs, typename SType>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_ms_div(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, SType v2)
    {
        return {v1.components[Idxs] / v2...};
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs, typename SType>
    static constexpr bool matrix_ms_eq(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, SType v2)
    {
#ifndef _MSC_VER
        return ((v1.components[Idxs] == v2) && ...);
#else
        bool ret = true;
        (void)(ar_t{((ret = ret && v1.components[Idxs] == v2), 0)...});
        return ret;
#endif
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs, typename SType>
    static constexpr bool matrix_ms_neq(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType, Kind>& v1, SType v2)
    {
#ifndef _MSC_VER
        return ((v1.components[Idxs] != v2) && ...);
#else
        bool ret = true;
        (void)(ar_t{((ret = ret && v1.components[Idxs] != v2), 0)...});
        return ret;
#endif
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr auto operator + (const matrix<DimX, DimY, VType, Kind>& v1, SType&& v2) -> auto
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_ms_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return matrix_mm_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr auto operator - (const matrix<DimX, DimY, VType, Kind>& v1, SType&& v2) -> auto
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_ms_sub(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return matrix_mm_sub(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr auto operator * (const matrix<DimX, DimY, VType, Kind>& v1, SType&& v2) -> auto
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_ms_mul(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return matrix_mm_mul(v1, v2);
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr auto operator / (const matrix<DimX, DimY, VType, Kind>& v1, SType&& v2) -> auto
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_ms_div(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return matrix_mm_div(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr bool operator == (const matrix<DimX, DimY, VType, Kind>& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_ms_eq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else if constexpr (std::is_same<matrix<DimX, DimY, VType, Kind>, SType>::value)
            return matrix_mm_eq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return false;
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr bool operator != (const matrix<DimX, DimY, VType, Kind>& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_ms_neq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else if constexpr (std::is_same<matrix<DimX, DimY, VType, Kind>, SType>::value)
            return matrix_mm_neq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return false;
    }

    // scalar - matrix operations

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_sm_add(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
        return {v1 + v2.components[Idxs]...};
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_sm_sub(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
        return {v1 - v2.components[Idxs]...};
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_sm_mul(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
        return {v1 * v2.components[Idxs]...};
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, typename remove_reference<VType>::type, Kind> matrix_sm_div(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
        return {v1 / v2.components[Idxs]...};
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr bool matrix_sm_eq(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
#ifndef _MSC_VER
        return ((v1 == v2.components[Idxs]) && ...);
#else
        bool ret = true;
        (void)(ar_t{((ret = ret && v1 == v2.components[Idxs]), 0)...});
        return ret;
#endif
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr bool matrix_sm_neq(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
#ifndef _MSC_VER
        return ((v1 != v2.components[Idxs]) && ...);
#else
        bool ret = true;
        (void)(ar_t{((ret = ret && v1 != v2.components[Idxs]), 0)...});
        return ret;
#endif
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind>
    constexpr auto operator + (VType v1, const matrix<DimX, DimY, VType, Kind>& v2) -> auto
    {
        return matrix_sm_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind>
    constexpr auto operator - (VType v1, const matrix<DimX, DimY, VType, Kind>& v2) -> auto
    {
        return matrix_sm_sub(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind>
    constexpr auto operator * (VType v1, const matrix<DimX, DimY, VType, Kind>& v2) -> auto
    {
        return matrix_sm_mul(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind>
    constexpr auto operator / (VType v1, const matrix<DimX, DimY, VType, Kind>& v2) -> auto
    {
        return matrix_sm_div(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind>
    constexpr bool operator == (VType v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
        return matrix_sm_eq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind>
    constexpr bool operator != (VType v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
        return matrix_sm_neq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }

    // self-matrix - matrix operations

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, VType, Kind>& matrix_smm_add(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType, Kind>& v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
#ifndef _MSC_VER
        ((v1.components[Idxs] += v2.components[Idxs]), ...);
#else
        using ar_t = int[];
        (void)(ar_t{((v1.components[Idxs] += v2.components[Idxs]), 0)...});
#endif
        return v1;
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, VType, Kind>& matrix_smm_sub(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType, Kind>& v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
#ifndef _MSC_VER
        ((v1.components[Idxs] -= v2.components[Idxs]), ...);
#else
        using ar_t = int[];
        (void)(ar_t{(v1.components[Idxs] -= v2.components[Idxs])...});
#endif
        return v1;
    }
    template<typename VType, size_t DimX1, size_t DimY1, size_t DimX2, size_t DimY2, matrix_kind Kind>
    constexpr matrix<DimX1, DimY1, VType, Kind>& matrix_smm_mul(matrix<DimX1, DimY1, VType, Kind>& v1, const matrix<DimX2, DimY2, VType, Kind>& v2)
    {
        // This static assert is necessary as with matrix multiplication of two matrices/vectors produces a potentially different type.
        // To multiply two matrices and make sure the result has the same type than the first matrix, the second one MUST be a square matrix with the same size
        // as the vertical size of the first one:
        // say you have a <4, 5> matrix, the only way to use *= is to multiply that <4, 5> matrix by a <5, 5> one
        // In a more general way, a <X, Y> matrix/vector can only be multiplied against a <Y, Y> matrix:
        //      <X, Y> *= <Y, Y>
        // Any other matrices will produce a different type and affectation will not work.
        static_assert(DimY1 == DimX2 && DimY2 == DimY1, "matrix *= operator can only be used when the other matrix is a square matrix of the same dimension of the DimY of the initial matrix");
        return (v1 = v1 * v2);
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX, DimY, VType, Kind>& matrix_smm_div(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType, Kind>& v1, const matrix<DimX, DimY, VType, Kind>& v2)
    {
#ifndef _MSC_VER
        ((v1.components[Idxs] /= v2.components[Idxs]), ...);
#else
        using ar_t = int[];
        (void)(ar_t{(v1.components[Idxs] /= v2.components[Idxs])...});
#endif
        return v1;
    }

    // self-matrix - scalar operations

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs, typename SType>
    static constexpr matrix<DimX, DimY, VType, Kind>& matrix_sms_add(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType, Kind>& v1, SType v2)
    {
#ifndef _MSC_VER
        ((v1.components[Idxs] += v2), ...);
#else
        using ar_t = int[];
        (void)(ar_t{((v1.components[Idxs] += v2), 0)...});
#endif
        return v1;
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs, typename SType>
    static constexpr matrix<DimX, DimY, VType, Kind>& matrix_sms_sub(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType, Kind>& v1, SType v2)
    {
#ifndef _MSC_VER
        ((v1.components[Idxs] -= v2), ...);
#else
        using ar_t = int[];
        (void)(ar_t{((v1.components[Idxs] -= v2), 0)...});
#endif
        return v1;
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs, typename SType>
    static constexpr matrix<DimX, DimY, VType, Kind>& matrix_sms_mul(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType, Kind>& v1, SType v2)
    {
#ifndef _MSC_VER
        ((v1.components[Idxs] *= v2), ...);
#else
        using ar_t = int[];
        (void)(ar_t{((v1.components[Idxs] *= v2), 0)...});
#endif
        return v1;
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, size_t... Idxs, typename SType>
    static constexpr matrix<DimX, DimY, VType, Kind>& matrix_sms_div(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType, Kind>& v1, SType v2)
    {
#ifndef _MSC_VER
        ((v1.components[Idxs] /= v2), ...);
#else
        using ar_t = int[];
        (void)(ar_t{((v1.components[Idxs] /= v2), 0)...});
#endif
        return v1;
    }

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr matrix<DimX, DimY, VType, Kind>& operator += (matrix<DimX, DimY, VType, Kind>& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_sms_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return matrix_smm_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr matrix<DimX, DimY, VType, Kind>& operator -= (matrix<DimX, DimY, VType, Kind>& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_sms_sub(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return matrix_smm_sub(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr matrix<DimX, DimY, VType, Kind>& operator *= (matrix<DimX, DimY, VType, Kind>& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_sms_mul(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return matrix_smm_mul(v1, v2);
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr matrix<DimX, DimY, VType, Kind>& operator /= (matrix<DimX, DimY, VType, Kind>& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return matrix_sms_div(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        else
            return matrix_smm_div(std::make_index_sequence<DimX * DimY>{}, v1, v2);
    }

    // rvalue

    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr matrix<DimX, DimY, VType, Kind>&& operator += (matrix<DimX, DimY, VType, Kind>&& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return static_cast<matrix<DimX, DimY, VType, Kind>&&>(matrix_sms_add(std::make_index_sequence<DimX * DimY>{}, v1, v2));
        else
            return static_cast<matrix<DimX, DimY, VType, Kind>&&>(matrix_smm_add(std::make_index_sequence<DimX * DimY>{}, v1, v2));
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr matrix<DimX, DimY, VType, Kind>&& operator -= (matrix<DimX, DimY, VType, Kind>&& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return static_cast<matrix<DimX, DimY, VType, Kind>&&>(matrix_sms_sub(std::make_index_sequence<DimX * DimY>{}, v1, v2));
        else
            return static_cast<matrix<DimX, DimY, VType, Kind>&&>(matrix_smm_sub(std::make_index_sequence<DimX * DimY>{}, v1, v2));
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr matrix<DimX, DimY, VType, Kind>&& operator *= (matrix<DimX, DimY, VType, Kind>&& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return static_cast<matrix<DimX, DimY, VType, Kind>&&>(matrix_sms_mul(std::make_index_sequence<DimX * DimY>{}, v1, v2));
        else
            return static_cast<matrix<DimX, DimY, VType, Kind>&&>(matrix_smm_mul(v1, v2));
    }
    template<typename VType, size_t DimX, size_t DimY, matrix_kind Kind, typename SType>
    constexpr matrix<DimX, DimY, VType, Kind>&& operator /= (matrix<DimX, DimY, VType, Kind>&& v1, SType&& v2)
    {
        if constexpr(std::is_arithmetic<SType>::value || is_fixed_point<SType>::value || is_reference<SType>::value || std::is_same<SType, VType>::value)
            return static_cast<matrix<DimX, DimY, VType, Kind>&&>(matrix_sms_div(std::make_index_sequence<DimX * DimY>{}, v1, v2));
        else
            return static_cast<matrix<DimX, DimY, VType, Kind>&&>(matrix_smm_div(std::make_index_sequence<DimX * DimY>{}, v1, v2));
    }
} // namespace cml::implementation
