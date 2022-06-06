// Copyright (c) 2022 Papa Libasse Sow.
// https://github.com/Nandite/bazaar_traits
// Distributed under the MIT Software License (X11 license).
//
// SPDX-License-Identifier: MIT
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of
// the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef INTEGER_SEQUENCE_HPP
#define INTEGER_SEQUENCE_HPP

#include <cstddef>
#include "bazaar_traits.hpp"

namespace bazaar::traits {

    template<typename Tp, Tp ... Idx>
    struct integer_sequence {
        static_assert(is_integral_v<Tp>, "bzt::integer_sequence requires an integral type");
        using value_type = Tp;
        static constexpr std::size_t size() noexcept {return sizeof ...(Idx);}
    };

    template<std::size_t ... Idx> using index_sequence = integer_sequence<std::size_t, Idx...>;

    namespace impl
    {
        template<std::size_t ... Sequence>
        struct convertible_index_sequence {
            using type = convertible_index_sequence;

            template<template<typename Up, Up ...> typename NewSequence, typename NewType>
            using convert = NewSequence<NewType, Sequence...>;
        };

        template<typename I1, typename I2>
        struct merge_recount_sequence;

        template<std::size_t ... LeftSequence, std::size_t ... RightSequence>
        struct merge_recount_sequence<convertible_index_sequence<LeftSequence...>,
                convertible_index_sequence<RightSequence...>>
                : public convertible_index_sequence<LeftSequence..., (sizeof...(LeftSequence) +
                                                                                   RightSequence)...> {
        };

        template<std::size_t N>
        struct make_index_sequence_impl : merge_recount_sequence<
                typename make_index_sequence_impl<N/2>::type,
                typename make_index_sequence_impl<N - N/2>::type
                >{};

        template<> struct make_index_sequence_impl<0> : convertible_index_sequence<> {};
        template<> struct make_index_sequence_impl<1> : convertible_index_sequence<0> {};

        template<typename Tp, Tp N>
        using make_integer_sequence_nocheck =
                typename make_index_sequence_impl<N>::template convert<integer_sequence, Tp>;

        template<typename Tp, Tp N>
        struct make_integer_sequence_checked : public identity<make_integer_sequence_nocheck<Tp,  N >= 0 ? N : 0>>
        {
            static_assert(is_integral_v<Tp>, "bzt::make_integer_sequence requires an integral type");
            static_assert(N >= 0, "bzt::make_integer_sequence must have a non-negative sequence length");
        };

    }

    template<std::size_t N>
    using make_index_sequence = typename impl::make_index_sequence_impl<N>
            ::template convert<integer_sequence, std::size_t>;

    template<typename Tp, Tp N>
    using make_integer_sequence =
#if BZT_HAS_BUILTIN(__make_integer_seq)// Clang
            __make_integer_seq<integer_sequence, Tp, N>;
#else       // Other compilers
            typename impl::make_integer_sequence_checked<Tp,N>::type;
#endif

    template<typename ... Tp>
    using index_sequence_for = make_index_sequence<sizeof ... (Tp)>;
}

#endif //INTEGER_SEQUENCE_HPP
