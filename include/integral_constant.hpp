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

#pragma once

namespace bazaar::traits
{
    template<typename Tp, Tp v>
    struct integral_constant{
        static constexpr Tp value = v;
        using value_type = Tp;
        using type = integral_constant;
        constexpr explicit operator value_type () const noexcept {return value;}
        constexpr value_type operator()() const noexcept{return value;}
    };

    template<bool v>
    using bool_constant = integral_constant<bool, v>;

    using true_type = bool_constant<true>;
    using false_type = bool_constant<false>;

    namespace impl {
        template<typename Tp>
        struct invert_bool_constant : public bool_constant<!bool(Tp::value)> {};
        template<typename Tp>
        using invert_bool_constant_t = typename invert_bool_constant<Tp>::type;
    }
}