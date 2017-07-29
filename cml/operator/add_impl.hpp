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

#include "../traits.hpp"

namespace cml::implementation
{
    template<typename MType, size_t... Idxs>
    static constexpr remove_matrix_reference_t<MType> matrix_mm_add(std::index_sequence<Idxs...>, const MType& v1, const MType& v2)
    {
        return {v1.components[Idxs] + v2.components[Idxs]...};
    }

    template<typename MType, typename SType, size_t... Idxs>
    static constexpr remove_matrix_reference_t<MType> matrix_ms_add(std::index_sequence<Idxs...>, const MType& v1, SType&& v2)
    {
        return {v1.components[Idxs] + v2...};
    }

    template<typename MType, typename SType, size_t... Idxs>
    static constexpr remove_matrix_reference_t<MType> matrix_sm_add(std::index_sequence<Idxs...>, SType&& v1, const MType& v2)
    {
        return {v1 + v2.components[Idxs]...};
    }

    template<typename MType, size_t... Idxs>
    static constexpr MType& matrix_smm_add(std::index_sequence<Idxs...>, MType& v1, const MType& v2)
    {
#ifndef _MSC_VER
        ((v1.components[Idxs] += v2.components[Idxs]), ...);
#else
        using ar_t = int[];
        (void)(ar_t{((v1.components[Idxs] += v2.components[Idxs]), 0)...});
#endif
        return v1;
    }

    template<typename MType, typename SType, size_t... Idxs>
    static constexpr MType& matrix_sms_add(std::index_sequence<Idxs...>, MType& v1, SType&& v2)
    {
#ifndef _MSC_VER
        ((v1.components[Idxs] += v2), ...);
#else
        using ar_t = int[];
        (void)(ar_t{((v1.components[Idxs] += v2), 0)...});
#endif
        return v1;
    }
}
