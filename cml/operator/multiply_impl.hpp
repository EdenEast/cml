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

#include "../functions/dot.hpp"
#include "../functions/cross.hpp"
#include "../traits.hpp"

namespace cml::implementation
{
    template<size_t Idx, typename VType, size_t DimX1, size_t DimY1, size_t DimX2, size_t DimY2, matrix_kind Kind, size_t... Idxs, size_t... CommonIdxs>
    static constexpr VType matrix_mm_mul_dot(std::index_sequence<CommonIdxs...>, const matrix<DimX1, DimY1, VType, Kind>& v1, const matrix<DimX2, DimY2, VType, Kind>& v2)
    {
        constexpr size_t x = Idx % DimX2;
        constexpr size_t y = Idx / DimX2;

#ifndef _MSC_VER
        return ((v1.components[CommonIdxs + y * DimX1] * v2.components[x + CommonIdxs * DimX2]) + ...);
#else
        using ar_t = int[];
        VType ret = VType(0);
        (void)(ar_t {((ret += v1.components[CommonIdxs + y * DimX1] * v2.components[x + CommonIdxs * DimX2]), 0)...});
        return ret;
#endif
    }

    template<typename VType, size_t DimX1, size_t DimY1, size_t DimX2, size_t DimY2, matrix_kind Kind, size_t... Idxs>
    static constexpr matrix<DimX2, DimY1, typename remove_reference<VType>::type, Kind> matrix_mm_mul(std::index_sequence<Idxs...>, const matrix<DimX1, DimY1, VType, Kind>& v1, const matrix<DimX2, DimY2, VType, Kind>& v2)
    {
        return {matrix_mm_mul_dot<Idxs>(std::make_index_sequence<DimY2>{}, v1, v2)...};
    }

    template<typename VType, size_t DimX1, size_t DimY1, size_t DimX2, size_t DimY2, matrix_kind Kind>
    constexpr auto matrix_mm_mul(const matrix<DimX1, DimY1, VType, Kind>& v1, const matrix<DimX2, DimY2, VType, Kind>& v2) -> auto
    {
        static_assert(DimX1 == DimY2, "Cannot multiply matrices when the number of columns of the first matrix is different from the number of rows of the second matrix");
        return matrix_mm_mul(std::make_index_sequence<DimX2 * DimY1>{}, v1, v2);
    }

    template<typename MType, typename SType, size_t... Idxs>
    static constexpr remove_matrix_reference_t<MType> matrix_ms_mul(std::index_sequence<Idxs...>, const MType& v1, SType&& v2)
    {
        return {v1.components[Idxs] * v2...};
    }

    template<typename SType, typename MType, size_t... Idxs>
    static constexpr remove_matrix_reference_t<MType> matrix_sm_mul(std::index_sequence<Idxs...>, SType&& v1, const MType& v2)
    {
        return {v1 * v2.components[Idxs]...};
    }

    template<typename M1, typename M2>
    constexpr M1& matrix_smm_mul(M1& v1, const M2& v2)
    {
        // This static assert is necessary as with matrix multiplication of two matrices/vectors produces a potentially different type.
        // To multiply two matrices and make sure the result has the same type than the first matrix, the second one MUST be a square matrix with the same size
        // as the vertical size of the first one:
        // say you have a <4, 5> matrix, the only way to use *= is to multiply that <4, 5> matrix by a <5, 5> one
        // In a more general way, a <X, Y> matrix/vector can only be multiplied against a <Y, Y> matrix:
        //      <X, Y> *= <Y, Y>
        // Any other matrices will produce a different type and affectation will not work.
        static_assert(matrix_traits<M1>::dimy == matrix_traits<M2>::dimx && matrix_traits<M1>::dimy == matrix_traits<M2>::dimy, "matrix *= operator can only be used when the other matrix is a square matrix of the same dimension of the DimY of the initial matrix");
        return (v1 = v1 * v2);
    }

    template<typename MType, typename SType, size_t... Idxs>
    static constexpr MType& matrix_sms_mul(std::index_sequence<Idxs...>, MType& v1, SType&& v2)
    {
#ifndef _MSC_VER
        ((v1.components[Idxs] *= v2), ...);
#else
        using ar_t = int[];
        (void)(ar_t{((v1.components[Idxs] *= v2), 0)...});
#endif
        return v1;
    }

    template<typename QType>
    constexpr quaternion<QType> quat_qq_mul(const quaternion<QType>& v1, const quaternion<QType>& v2)
    {
        return quaternion<QType>(
            (v1.components[3] * v2.components[0] + v1.components[0] * v2.components[3] + v1.components[1] * v2.components[2] - v1.components[2] * v2.components[1]),
            (v1.components[3] * v2.components[1] - v1.components[0] * v2.components[2] + v1.components[1] * v2.components[3] + v1.components[2] * v2.components[0]),
            (v1.components[3] * v2.components[2] + v1.components[0] * v2.components[1] - v1.components[1] * v2.components[0] + v1.components[2] * v2.components[3]),
            (v1.components[3] * v2.components[3] - v1.components[0] * v2.components[0] - v1.components[1] * v2.components[1] - v1.components[2] * v2.components[2])
        );
    }

    template<typename QType, typename VType>
    constexpr auto quat_qv_mul(const quaternion<QType>& q, VType&& v)
    {
        // https://gamedev.stackexchange.com/a/50545
        constexpr auto vp = q.vec_part();
        constexpr auto sp = q.scalar_part();
        return QType(QType(2) * dot(vp, v) * vp + (sp*sp - dot(vp, vp)) * v + QType(2) * sp * cross(vp, v));
    }

    template<typename QType, typename SType>
    constexpr auto quat_qs_mul(const quaternion<QType>& q, SType&& s)
    {
        auto axis = q.scalar_part() > 0 ? q.vector_part() : -q.vector_part();
        auto angle = SType(2) * atan2(normalize(axis), q.scalar_part() > 0 ? q.scalar_part() : -q.scalar_part());
        angle *= s;
        return quaternion<QType>(normalize(axis) * sin(SType{0.5} * angle), cos(SType{0.5} * angle));
    }

    template<typename VType, typename SType>
    constexpr auto quat_mul(const VType& v1, SType&& v2) -> auto
    {
        // guarentied that one of the values will be a quat just not sure what one is.
        if constexpr(is_quaternion<VType>::value && is_quaternion<SType>::value)
            return quat_qq_mul(v1, v2);
        else if constexpr(is_vector<VType>::value || is_vector<SType>::value)
        {
            // since we know that one if the values is a quaternion we just have to figure out what one is the vector
            using vector_type = std::conditional_t<is_vector<VType>::value, VType, SType>;
            constexpr auto dim = matrix_traits<vector_type>::dimx > matrix_traits<vector_type>::dimy ? matrix_traits<vector_type>::dimx : matrix_traits<vector_type>::dimy;
            static_assert(dim == 3, "can only multiply a quaternion by a 3 component vector");
            return quat_qv_mul(v1, v2);
        }
        else
        {
            // if the other value is not a quaternion or a vecetor then the last value is a scalar
            return quat_qs_mul(v1, v2);
        }
    }
}
