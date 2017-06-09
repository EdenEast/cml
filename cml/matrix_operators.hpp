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

namespace cml
{
    namespace implementation
    {
#ifdef _MSC_VER
		using ar_t = int[];
#endif
		
		// matrix - matrix operations

        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType> matrix_mm_add(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix<DimX, DimY, VType>{v1.components[Idxs] + v2.components[Idxs]...};
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType> matrix_mm_sub(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix<DimX, DimY, VType>{v1.components[Idxs] - v2.components[Idxs]...};
        }
        template<typename VType, size_t DimX1, size_t DimY1, size_t DimX2, size_t DimY2, size_t... Idxs>
        static constexpr matrix<DimX1, DimY2, VType> matrix_mm_mul(std::index_sequence<Idxs...>, const matrix<DimX1, DimY1, VType>& v1, const matrix<DimX2, DimY2, VType>& v2)
        {
            // TODO
            return matrix<DimX1, DimY2, VType>{v1.components[Idxs] * v2.components[Idxs]...};
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType> matrix_mm_div(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix<DimX, DimY, VType>{v1.components[Idxs] / v2.components[Idxs]...};
        }

        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr bool matrix_mm_eq(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
#ifndef _MSC_VER
			return ((v1.components[Idxs] == v2.components[Idxs]) && ...);
#else
			bool ret = true;
			(void)(ar_t{((ret = ret && v1.components[Idxs] == v2.components[Idxs]), 0)...});
			return ret;
#endif
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr bool matrix_mm_neq(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
#ifndef _MSC_VER
			return ((v1.components[Idxs] != v2.components[Idxs]) && ...);
#else
			bool ret = true;
			(void)(ar_t{((ret = ret && v1.components[Idxs] != v2.components[Idxs]), 0)...});
			return ret;
#endif
        }

        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType> operator + (const matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_mm_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType> operator - (const matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_mm_sub(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX1, size_t DimY1, size_t DimX2, size_t DimY2>
        constexpr matrix<DimX1, DimY2, VType> operator * (const matrix<DimX1, DimY1, VType>& v1, const matrix<DimX2, DimY2, VType>& v2)
        {
            static_assert(DimX1 == DimY2, "Cannot multiply matrices when the number of columns of the first matrix is different from the number of rows of the second matrix");
            return matrix_mm_mul(std::make_index_sequence<DimX1 * DimY2>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType> operator / (const matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_mm_div(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }

        template<typename VType, size_t DimX, size_t DimY>
        constexpr bool operator == (const matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_mm_eq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr bool operator != (const matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_mm_neq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }

        // matrix - scalar operations

        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType> matrix_ms_add(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix<DimX, DimY, VType>{v1.components[Idxs] + v2...};
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType> matrix_ms_sub(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix<DimX, DimY, VType>{v1.components[Idxs] - v2...};
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType> matrix_ms_mul(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix<DimX, DimY, VType>{v1.components[Idxs] * v2...};
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType> matrix_ms_div(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix<DimX, DimY, VType>{v1.components[Idxs] / v2...};
        }

        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr bool matrix_ms_eq(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType>& v1, VType v2)
        {
#ifndef _MSC_VER
			return ((v1.components[Idxs] == v2) && ...);
#else
			bool ret = true;
			(void)(ar_t{((ret = ret && v1.components[Idxs] == v2), 0)...});
			return ret;
#endif
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr bool matrix_ms_neq(std::index_sequence<Idxs...>, const matrix<DimX, DimY, VType>& v1, VType v2)
        {
#ifndef _MSC_VER
			return ((v1.components[Idxs] != v2) && ...);
#else
			bool ret = true;
			(void)(ar_t{((ret = ret && v1.components[Idxs] != v2), 0)...});
			return ret;
#endif
        }

        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType> operator + (const matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix_ms_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType> operator - (const matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix_ms_sub(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType> operator * (const matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix_ms_mul(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType> operator / (const matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix_ms_div(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }

        template<typename VType, size_t DimX, size_t DimY>
        constexpr bool operator == (const matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix_ms_eq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr bool operator != (const matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix_ms_neq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }

        // scalar - matrix operations

        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType> matrix_sm_add(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix<DimX, DimY, VType>{v1 + v2.components[Idxs]...};
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType> matrix_sm_sub(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix<DimX, DimY, VType>{v1 - v2.components[Idxs]...};
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType> matrix_sm_mul(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix<DimX, DimY, VType>{v1 * v2.components[Idxs]...};
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType> matrix_sm_div(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix<DimX, DimY, VType>{v1 / v2.components[Idxs]...};
        }

        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr bool matrix_sm_eq(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType>& v2)
        {
#ifndef _MSC_VER
			return ((v1 == v2.components[Idxs]) && ...);
#else
			bool ret = true;
			(void)(ar_t{((ret = ret && v1 == v2.components[Idxs]), 0)...});
			return ret;
#endif
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr bool matrix_sm_neq(std::index_sequence<Idxs...>, VType v1, const matrix<DimX, DimY, VType>& v2)
        {
#ifndef _MSC_VER
			return ((v1 != v2.components[Idxs]) && ...);
#else
			bool ret = true;
			(void)(ar_t{((ret = ret && v1 != v2.components[Idxs]), 0)...});
			return ret;
#endif
        }

        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType> operator + (VType v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_sm_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType> operator - (VType v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_sm_sub(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType> operator * (VType v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_sm_mul(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType> operator / (VType v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_sm_div(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }

        template<typename VType, size_t DimX, size_t DimY>
        constexpr bool operator == (VType v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_sm_eq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr bool operator != (VType v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_sm_neq(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }

        // self-matrix - matrix operations

        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType>& matrix_smm_add(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] += v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{((v1.components[Idxs] += v2.components[Idxs]), 0)...});
#endif
            return v1;
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType>& matrix_smm_sub(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] -= v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{(v1.components[Idxs] -= v2.components[Idxs])...});
#endif
            return v1;
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType>& matrix_smm_mul(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] *= v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{(v1.components[Idxs] *= v2.components[Idxs])...});
#endif
            return v1;
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType>& matrix_smm_div(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] /= v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{(v1.components[Idxs] /= v2.components[Idxs])...});
#endif
            return v1;
        }


        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType>& operator += (matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_smm_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType>& operator -= (matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_smm_sub(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType>& operator *= (matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_smm_mul(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType>& operator /= (matrix<DimX, DimY, VType>& v1, const matrix<DimX, DimY, VType>& v2)
        {
            return matrix_smm_div(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }

        // self-matrix - scalar operations

        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType>& matrix_sms_add(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType>& v1, VType v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] += v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{((v1.components[Idxs] += v2.components[Idxs]), 0)...});
#endif
            return v1;
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType>& matrix_sms_sub(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType>& v1, VType v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] -= v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{((v1.components[Idxs] -= v2.components[Idxs]), 0)...});
#endif
            return v1;
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType>& matrix_sms_mul(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType>& v1, VType v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] *= v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{((v1.components[Idxs] *= v2.components[Idxs]), 0)...});
#endif
            return v1;
        }
        template<typename VType, size_t DimX, size_t DimY, size_t... Idxs>
        static constexpr matrix<DimX, DimY, VType>& matrix_sms_div(std::index_sequence<Idxs...>, matrix<DimX, DimY, VType>& v1, VType v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] /= v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{((v1.components[Idxs] /= v2.components[Idxs]), 0)...});
#endif
            return v1;
        }


        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType>& operator += (matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix_sms_add(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType>& operator -= (matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix_sms_sub(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType>& operator *= (matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix_sms_mul(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
        template<typename VType, size_t DimX, size_t DimY>
        constexpr matrix<DimX, DimY, VType>& operator /= (matrix<DimX, DimY, VType>& v1, VType v2)
        {
            return matrix_sms_div(std::make_index_sequence<DimX * DimY>{}, v1, v2);
        }
    } // namespace implementation
} // namespace cml
