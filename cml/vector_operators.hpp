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
#include "vector.hpp"

namespace cml
{
    namespace implementation
    {
        // vector - vector operations

        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType> vector_vv_add(std::index_sequence<Idxs...>, const vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector<Dim, VType>{v1.components[Idxs] + v2.components[Idxs]...};
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType> vector_vv_sub(std::index_sequence<Idxs...>, const vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector<Dim, VType>{v1.components[Idxs] - v2.components[Idxs]...};
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType> vector_vv_mul(std::index_sequence<Idxs...>, const vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector<Dim, VType>{v1.components[Idxs] * v2.components[Idxs]...};
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType> vector_vv_div(std::index_sequence<Idxs...>, const vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector<Dim, VType>{v1.components[Idxs] / v2.components[Idxs]...};
        }

        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr bool vector_vv_eq(std::index_sequence<Idxs...>, const vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return ((v1.components[Idxs] == v2.components[Idxs]) && ...);
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr bool vector_vv_neq(std::index_sequence<Idxs...>, const vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return ((v1.components[Idxs] != v2.components[Idxs]) && ...);
        }

        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType> operator + (const vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector_vv_add(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType> operator - (const vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector_vv_sub(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType> operator * (const vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector_vv_mul(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType> operator / (const vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector_vv_div(std::make_index_sequence<Dim>{}, v1, v2);
        }

        template<typename VType, size_t Dim>
        constexpr bool operator == (const vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector_vv_eq(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr bool operator != (const vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector_vv_neq(std::make_index_sequence<Dim>{}, v1, v2);
        }

        // vector - scalar operations

        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType> vector_vs_add(std::index_sequence<Idxs...>, const vector<Dim, VType>& v1, VType v2)
        {
            return vector<Dim, VType>{v1.components[Idxs] + v2...};
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType> vector_vs_sub(std::index_sequence<Idxs...>, const vector<Dim, VType>& v1, VType v2)
        {
            return vector<Dim, VType>{v1.components[Idxs] - v2...};
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType> vector_vs_mul(std::index_sequence<Idxs...>, const vector<Dim, VType>& v1, VType v2)
        {
            return vector<Dim, VType>{v1.components[Idxs] * v2...};
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType> vector_vs_div(std::index_sequence<Idxs...>, const vector<Dim, VType>& v1, VType v2)
        {
            return vector<Dim, VType>{v1.components[Idxs] / v2...};
        }

        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr bool vector_vs_eq(std::index_sequence<Idxs...>, const vector<Dim, VType>& v1, VType v2)
        {
            return ((v1.components[Idxs] == v2) && ...);
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr bool vector_vs_neq(std::index_sequence<Idxs...>, const vector<Dim, VType>& v1, VType v2)
        {
            return ((v1.components[Idxs] != v2) && ...);
        }

        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType> operator + (const vector<Dim, VType>& v1, VType v2)
        {
            return vector_vs_add(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType> operator - (const vector<Dim, VType>& v1, VType v2)
        {
            return vector_vs_sub(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType> operator * (const vector<Dim, VType>& v1, VType v2)
        {
            return vector_vs_mul(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType> operator / (const vector<Dim, VType>& v1, VType v2)
        {
            return vector_vs_div(std::make_index_sequence<Dim>{}, v1, v2);
        }

        template<typename VType, size_t Dim>
        constexpr bool operator == (const vector<Dim, VType>& v1, VType v2)
        {
            return vector_vs_eq(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr bool operator != (const vector<Dim, VType>& v1, VType v2)
        {
            return vector_vs_neq(std::make_index_sequence<Dim>{}, v1, v2);
        }

        // scalar - vector operations

        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType> vector_sv_add(std::index_sequence<Idxs...>, VType v1, const vector<Dim, VType>& v2)
        {
            return vector<Dim, VType>{v1 + v2.components[Idxs]...};
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType> vector_sv_sub(std::index_sequence<Idxs...>, VType v1, const vector<Dim, VType>& v2)
        {
            return vector<Dim, VType>{v1 - v2.components[Idxs]...};
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType> vector_sv_mul(std::index_sequence<Idxs...>, VType v1, const vector<Dim, VType>& v2)
        {
            return vector<Dim, VType>{v1 * v2.components[Idxs]...};
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType> vector_sv_div(std::index_sequence<Idxs...>, VType v1, const vector<Dim, VType>& v2)
        {
            return vector<Dim, VType>{v1 / v2.components[Idxs]...};
        }

        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr bool vector_sv_eq(std::index_sequence<Idxs...>, VType v1, const vector<Dim, VType>& v2)
        {
            return ((v1 == v2.components[Idxs]) && ...);
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr bool vector_sv_neq(std::index_sequence<Idxs...>, VType v1, const vector<Dim, VType>& v2)
        {
            return ((v1 != v2.components[Idxs]) && ...);
        }

        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType> operator + (VType v1, const vector<Dim, VType>& v2)
        {
            return vector_sv_add(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType> operator - (VType v1, const vector<Dim, VType>& v2)
        {
            return vector_sv_sub(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType> operator * (VType v1, const vector<Dim, VType>& v2)
        {
            return vector_sv_mul(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType> operator / (VType v1, const vector<Dim, VType>& v2)
        {
            return vector_sv_div(std::make_index_sequence<Dim>{}, v1, v2);
        }

        template<typename VType, size_t Dim>
        constexpr bool operator == (VType v1, const vector<Dim, VType>& v2)
        {
            return vector_sv_eq(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr bool operator != (VType v1, const vector<Dim, VType>& v2)
        {
            return vector_sv_neq(std::make_index_sequence<Dim>{}, v1, v2);
        }

        // self-vector - vector operations

        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType>& vector_svv_add(std::index_sequence<Idxs...>, vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] += v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{(v1.components[Idxs] += v2.components[Idxs])...});
#endif
            return v1;
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType>& vector_svv_sub(std::index_sequence<Idxs...>, vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] -= v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{(v1.components[Idxs] -= v2.components[Idxs])...});
#endif
            return v1;
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType>& vector_svv_mul(std::index_sequence<Idxs...>, vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] *= v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{(v1.components[Idxs] *= v2.components[Idxs])...});
#endif
            return v1;
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType>& vector_svv_div(std::index_sequence<Idxs...>, vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] /= v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{(v1.components[Idxs] /= v2.components[Idxs])...});
#endif
            return v1;
        }


        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType>& operator += (vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector_svv_add(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType>& operator -= (vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector_svv_sub(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType>& operator *= (vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector_svv_mul(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType>& operator /= (vector<Dim, VType>& v1, const vector<Dim, VType>& v2)
        {
            return vector_svv_div(std::make_index_sequence<Dim>{}, v1, v2);
        }

        // self-vector - scalar operations

        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType>& vector_svs_add(std::index_sequence<Idxs...>, vector<Dim, VType>& v1, VType v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] += v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{(v1.components[Idxs] += v2.components[Idxs])...});
#endif
            return v1;
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType>& vector_svs_sub(std::index_sequence<Idxs...>, vector<Dim, VType>& v1, VType v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] -= v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{(v1.components[Idxs] -= v2.components[Idxs])...});
#endif
            return v1;
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType>& vector_svs_mul(std::index_sequence<Idxs...>, vector<Dim, VType>& v1, VType v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] *= v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{(v1.components[Idxs] *= v2.components[Idxs])...});
#endif
            return v1;
        }
        template<typename VType, size_t Dim, size_t... Idxs>
        static constexpr vector<Dim, VType>& vector_svs_div(std::index_sequence<Idxs...>, vector<Dim, VType>& v1, VType v2)
        {
#ifndef _MSC_VER
            ((v1.components[Idxs] /= v2.components[Idxs]), ...);
#else
            using ar_t = int[];
            (void)(ar_t{(v1.components[Idxs] /= v2.components[Idxs])...});
#endif
            return v1;
        }


        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType>& operator += (vector<Dim, VType>& v1, VType v2)
        {
            return vector_svs_add(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType>& operator -= (vector<Dim, VType>& v1, VType v2)
        {
            return vector_svs_sub(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType>& operator *= (vector<Dim, VType>& v1, VType v2)
        {
            return vector_svs_mul(std::make_index_sequence<Dim>{}, v1, v2);
        }
        template<typename VType, size_t Dim>
        constexpr vector<Dim, VType>& operator /= (vector<Dim, VType>& v1, VType v2)
        {
            return vector_svs_div(std::make_index_sequence<Dim>{}, v1, v2);
        }
    } // namespace implementation
} // namespace cml
