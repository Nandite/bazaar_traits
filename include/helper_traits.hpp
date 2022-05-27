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

#ifndef HELPER_TRAITS_HPP
#define HELPER_TRAITS_HPP

#include "integral_constant.hpp"

namespace bazaar::traits
{
    //-------------------------------------------------------------------------------------------
    // Helper traits
    //-------------------------------------------------------------------------------------------

    // nullptr_t
    using nullptr_t = decltype(nullptr);

    // void_t
    template<typename ...> using void_t = void;

    // Identity
    template<typename Tp>
    struct identity {using type = Tp;};

    // Enable_if
    template<bool, typename Tp = void>
    struct enable_if : public identity<Tp> {};

    template<typename Tp>
    struct enable_if<false, Tp> {};

    template<bool Condition, typename Tp>
    using enable_if_t [[maybe_unused]] = typename enable_if<Condition, Tp>::type;

    // Conditional
    namespace impl {

        template<bool Condition, typename If, typename>
        struct conditional_impl : public identity<If> {
        };

        template<typename If, typename Else>
        struct conditional_impl<false, If, Else> : public identity<Else> {
        };
    }

    template<bool Condition, typename If, typename Else>
    struct conditional : public impl::conditional_impl<Condition, If, Else>{};

    template<bool Condition, typename If, typename Else>
    using conditional_t [[maybe_unused]] = typename conditional<Condition, If, Else>::type;

    template<bool Condition>
    struct bool_condition : public impl::conditional_impl<Condition, true_type , false_type>{};

    // Is same
    namespace impl {
        template<typename Tp, typename Up>
        struct is_same_impl : public false_type {
        };

        template<typename Tp>
        struct is_same_impl<Tp, Tp> : public true_type {
        };
    }

    template<typename Tp, typename Up>
    struct is_same : public impl::is_same_impl<Tp,Up> {};

    template<typename Tp, typename Up>
    using is_not_same = impl::invert_bool_constant_t<typename impl::is_same_impl<Tp,Up>::type>;

    template<typename Tp, typename Up>
    inline constexpr bool is_same_v = is_same<Tp, Up>::value;

    template<typename Tp, typename Up>
    [[maybe_unused]] inline constexpr bool is_not_same_v = is_not_same<Tp, Up>::value;

    // Is one of
    namespace impl
    {
        template<typename, typename ...> struct is_one_of_impl;
        template<typename Tp> struct is_one_of_impl <Tp> : public false_type {};
        template<typename Tp, typename ... Sequence> struct is_one_of_impl<Tp, Tp, Sequence...> :  public true_type {};
        template<typename Tp, typename Up, typename ... Sequence>
        struct is_one_of_impl<Tp, Up, Sequence...> : public is_one_of_impl<Tp, Sequence...>{};

        template<typename Tp, typename ... Sequence>
        struct is_one_of : public impl::is_one_of_impl<Tp, Sequence...> {};

        template<typename Tp, typename ... Sequence>
        [[maybe_unused]] static constexpr auto is_one_of_v {is_one_of<Tp, Sequence...>::value};

        template<typename ... Sequence>
        using is_true_one_of [[maybe_unused]] = is_one_of<true_type, Sequence...>;

        template<typename ... Sequence>
        using is_false_one_of [[maybe_unused]] = is_one_of<false_type, Sequence...>;

        template<typename ... Sequence>
        [[maybe_unused]] static constexpr auto is_true_one_of_v {is_one_of<true_type, Sequence...>::value};

        template<typename ... Sequence>
        [[maybe_unused]] static constexpr auto is_false_one_of_v {is_one_of<false_type, Sequence...>::value};
    }
}

#endif //HELPER_TRAITS_HPP
