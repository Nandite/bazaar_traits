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

#ifndef BAZAAR_LOGICAL_OPERATORS_HPP
#define BAZAAR_LOGICAL_OPERATORS_HPP

#include "helper_traits.hpp"

namespace bazaar::traits
{
    //-------------------------------------------------------------------------------------------
    // [meta.logical], logical operator traits
    //-------------------------------------------------------------------------------------------

    // Conjunction
    namespace impl
    {
        template<typename ...>
        struct conjunction_impl : public true_type {};

        template<typename B0>
        struct conjunction_impl<B0> : public B0 {};

        template<typename B0, typename ... Bn>
        struct conjunction_impl<B0, Bn...> : public
                conditional_t<B0::value, conjunction_impl<Bn...>, B0>{};
    }

    template<typename ... Bn>
    struct conjunction : public impl::conjunction_impl<Bn...>{};

    template<typename ... Bn>
    [[maybe_unused]] inline constexpr auto conjunction_v{conjunction<Bn...>::value};

    // Disjunction
    namespace impl
    {
        template<typename ...>
        struct disjunction_impl : public false_type {};

        template<typename B0>
        struct disjunction_impl<B0> : public B0 {};

        template<typename B0, typename ... Bn>
        struct disjunction_impl<B0, Bn...> : public
                conditional_t<B0::value, B0, disjunction_impl<Bn...>> {};
    }

    template<typename ... Bn>
    struct disjunction : public impl::disjunction_impl<Bn...>{};

    template<typename ... Bn>
    [[maybe_unused]] inline constexpr auto disjunction_v {disjunction<Bn...>::value};

    // Negation
    template<typename B>
    struct negation : public impl::invert_bool_constant_t<B>{};

    template<typename B>
    [[maybe_unused]] inline constexpr auto negation_v {negation<B>::value};
}

#endif //BAZAAR_LOGICAL_OPERATORS_HPP
