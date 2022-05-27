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

#ifndef BAZAAR_ARITHMETIC_HPP
#define BAZAAR_ARITHMETIC_HPP

#include <cstddef>
#include "integral_constant.hpp"

namespace bazaar::traits
{
    //-------------------------------------------------------------------------------------------
    // Static arithmetic
    //-------------------------------------------------------------------------------------------

    // Max
    namespace impl {
        template<std::size_t I0, std::size_t ... In>
        struct static_max_impl {
        };

        template<std::size_t I0>
        struct static_max_impl<I0> {
            static constexpr auto value = I0;
        };

        template<std::size_t I0, std::size_t I1, std::size_t ... In>
        struct static_max_impl<I0, I1, In...> {
            static constexpr auto value =
                    I0 > I1 ? static_max_impl<I0, In...>::value : static_max_impl<I1, In...>::value;
        };
    }

    template<std::size_t ... Sequence>
    struct static_max : public impl::static_max_impl<Sequence...> {};

    template<std::size_t ... Sequence>
    [[maybe_unused]] inline constexpr auto static_max_v = static_max<Sequence...>::value;

    // Min
    namespace impl {
        template<std::size_t I0, std::size_t  ... In>
        struct static_min_impl {
        };

        template<std::size_t I0>
        struct static_min_impl<I0> {
            static constexpr auto value = I0;
        };

        template<std::size_t I0, std::size_t I1, std::size_t ... In>
        struct static_min_impl<I0, I1, In...> {
            static constexpr auto value =
                    I0 < I1 ? static_min_impl<I0, In...>::value : static_min_impl<I1, In...>::value;
        };
    }

    template<std::size_t ... Sequence>
    struct static_min : public impl::static_min_impl<Sequence...> {};

    template<std::size_t ... Sequence>
    [[maybe_unused]] inline constexpr auto static_min_v = static_min<Sequence...>::value;
}

#endif //BAZAAR_ARITHMETIC_HPP