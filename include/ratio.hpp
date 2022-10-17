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

#ifndef RATIO_HPP
#define RATIO_HPP

#include <cstdint>
#include "helper_traits.hpp"
#include "integral_constant.hpp"

namespace bazaar {
    namespace impl {
        template<std::intmax_t X, std::intmax_t Y>
        struct static_gcd : public static_gcd<Y, (X % Y)> {
        };

        template<std::intmax_t X>
        struct static_gcd<X, 0> : public traits::integral_constant<std::intmax_t, X> {
        };

        template<>
        struct static_gcd<0, 0> : public traits::integral_constant<std::intmax_t, 1> {
        };

        template<std::intmax_t X>
        struct static_abs : public traits::integral_constant<std::intmax_t, X < 0 ? -X : X> {
        };

        template<std::intmax_t X>
        struct static_sign : public traits::integral_constant<std::intmax_t, X == 0 ? 0 : (X < 0 ? -1 : 1)> {
        };

        struct overflow_arithmetic {
            constexpr static std::intmax_t nan{INTMAX_MIN};
            constexpr static std::intmax_t min{INTMAX_MIN + 1};
            constexpr static std::intmax_t max{INTMAX_MAX};
        };

        template<std::intmax_t X, std::intmax_t Y, std::intmax_t = static_sign<Y>::value>
        struct overflow_checked_add;

        template<std::intmax_t X, std::intmax_t Y>
        struct overflow_checked_add<X, Y, 1> : public overflow_arithmetic {
            static_assert(max - Y >= X, "overflow occurred for the addition");
            constexpr static std::intmax_t value{X + Y};
        };

        template<std::intmax_t X, std::intmax_t Y>
        struct overflow_checked_add<X, Y, -1> : public overflow_arithmetic {
            static_assert(min - Y <= X, "overflow occurred for the addition");
            constexpr static std::intmax_t value{X + Y};
        };

        template<std::intmax_t X, std::intmax_t Y>
        struct overflow_checked_add<X, Y, 0> {
            constexpr static std::intmax_t value{X};
        };

        template<std::intmax_t X, std::intmax_t Y, std::intmax_t = static_sign<Y>::value>
        struct overflow_checked_sub;

        template<std::intmax_t X, std::intmax_t Y>
        struct overflow_checked_sub<X, Y, 1> : public overflow_arithmetic {
            static_assert(min + Y <= X, "overflow occurred during subtraction");
            constexpr static std::intmax_t value{X - Y};
        };

        template<std::intmax_t X, std::intmax_t Y>
        struct overflow_checked_sub<X, Y, 0> {
            constexpr static std::intmax_t value{X};
        };

        template<std::intmax_t X, std::intmax_t Y>
        struct overflow_checked_sub<X, Y, -1> : public overflow_arithmetic {
            static_assert(max + Y >= X, "overflow occurred during subtraction");
        };

        template<std::intmax_t X, std::intmax_t Y, bool = (X == 0) || (Y == 0)>
        struct overflow_checked_mul;

        template<std::intmax_t X, std::intmax_t Y>
        struct overflow_checked_mul<X, Y, false> : public overflow_arithmetic {
            constexpr static std::intmax_t xAbs{static_abs<X>::value};
            constexpr static std::intmax_t yAbs{static_abs<Y>::value};
            static_assert(X != nan && Y != nan && xAbs <= (max / yAbs), "overflow occurred during multiplication");
            constexpr static std::intmax_t value{X * Y};
        };

        template<std::intmax_t X, std::intmax_t Y>
        struct overflow_checked_mul<X, Y, true> {
            constexpr static std::intmax_t value{0};
        };

        template<std::intmax_t X, std::intmax_t Y>
        struct overflow_checked_div : public overflow_arithmetic {
            static_assert(X != nan && Y != nan && Y != 0, "overflow occurred during division");
            constexpr static std::intmax_t value{X / Y};
        };
    }

    template<std::intmax_t Num, std::intmax_t Den = 1>
    class ratio {
        static_assert(impl::static_abs<Num>::value >= 0, "Numerator value is out of range");
        static_assert(Den != 0, "Trying to divide by zero");
        static_assert(impl::static_abs<Den>::value > 0, "Denominator value is out of range");
        constexpr static std::intmax_t sa{impl::static_sign<Num>::value};
        constexpr static std::intmax_t sd{impl::static_sign<Den>::value};
        constexpr static std::intmax_t na{impl::static_abs<Num>::value};
        constexpr static std::intmax_t da{impl::static_abs<Den>::value};
        constexpr static std::intmax_t gcd{impl::static_gcd<na, da>::value};
    public:
        constexpr static std::intmax_t num{sa * sd * na / gcd};
        constexpr static std::intmax_t den{da / gcd};
        using type = ratio<num, den>;
    };

    namespace impl {
        template<typename>
        struct is_ratio : public traits::false_type {
        };

        template<std::intmax_t Num, std::intmax_t Den>
        struct is_ratio<ratio<Num, Den>> : public traits::true_type {
        };
    }

    namespace impl {
        template<typename R1, typename R2, std::intmax_t gcdN1D2 = static_gcd<R1::num, R2::den>::value,
                std::intmax_t gcdN2D1 = static_gcd<R2::num, R1::den>::value>
        struct ratio_multiply_impl : public traits::identity<typename ratio<
                overflow_checked_mul<R1::num / gcdN1D2, R2::num / gcdN2D1>::value,
                overflow_checked_mul<R1::den / gcdN2D1, R2::den / gcdN1D2>::value>::type> {
        };

        template<typename R1, typename R2>
        struct ratio_multiply_checked_impl : public traits::identity<
                typename ratio_multiply_impl<R1, R2>::type
        > {
            static_assert(is_ratio<R1>::value, "R1 must be of ratio type");
            static_assert(is_ratio<R2>::value, "R2 must be of ratio type");
        };
    }

    template<typename R1, typename R2>
    using ratio_multiply [[maybe_unused]] = typename impl::ratio_multiply_checked_impl<R1, R2>::type;

    namespace impl {

        template<typename R1, typename R2, std::intmax_t gcdN1N2 = static_gcd<R1::num, R2::num>::value,
                std::intmax_t gcdD1D2 = static_gcd<R1::den, R2::den>::value>
        struct ratio_divide_impl : public traits::identity<typename ratio<
                overflow_checked_mul<R1::num / gcdN1N2, R2::den / gcdD1D2>::value,
                overflow_checked_mul<R2::num / gcdN1N2, R1::den / gcdD1D2>::value>::type> {

        };

        // Alternative
        // template<typename R1, typename R2>
        // struct ratio_divide_impl : public ratio_multiply_impl<R1, ratio<R2::den, R2::num>> {
        // };

        template<typename R1, typename R2>
        struct ratio_divide_checked_impl : public traits::identity<
                typename ratio_divide_impl<R1, R2>::type
        > {
            static_assert(is_ratio<R1>::value, "R1 must be of ratio type");
            static_assert(is_ratio<R2>::value, "R2 must be of ratio type");
        };
    }

    template<typename R1, typename R2>
    using ratio_divide [[maybe_unused]] = typename impl::ratio_divide_checked_impl<R1, R2>::type;

    namespace impl {
        template<typename R1, typename R2, std::intmax_t gcdN1N2 = static_gcd<R1::num, R2::num>::value,
                std::intmax_t gcdD1D2 = static_gcd<R1::den, R2::den>::value>
        struct ratio_add_impl : public traits::identity<typename ratio_multiply_impl<
                ratio<overflow_checked_add<overflow_checked_mul<R1::num / gcdN1N2, R2::den / gcdD1D2>::value,
                        overflow_checked_mul<
                                R2::num / gcdN1N2, R1::den / gcdD1D2>::value>::value, R1::den>, ratio<gcdN1N2,
                        R2::den / gcdD1D2>>::type> {
        };

        template<typename R1, typename R2>
        struct ratio_add_checked_impl : public traits::identity<
                typename ratio_add_impl<R1, R2>::type> {
            static_assert(is_ratio<R1>::value, "R1 must be of ratio type");
            static_assert(is_ratio<R2>::value, "R2 must be of ratio type");
        };
    }

    template<typename R1, typename R2>
    using ratio_add [[maybe_unused]] = typename impl::ratio_add_checked_impl<R1, R2>::type;

    namespace impl {
        template<typename R1, typename R2, std::intmax_t gcdN1N2 = static_gcd<R1::num, R2::num>::value,
                std::intmax_t gcdD1D2 = static_gcd<R1::den, R2::den>::value>
        struct ratio_sub_impl : public traits::identity<typename ratio_multiply_impl<
                ratio<overflow_checked_sub<overflow_checked_mul<R1::num / gcdN1N2, R2::den / gcdD1D2>::value,
                        overflow_checked_mul<R2::num / gcdN1N2, R1::den / gcdD1D2>::value>::value, R1::den>,
                ratio<gcdN1N2, R2::den / gcdD1D2>>::type> {
        };

        template<typename R1, typename R2>
        struct ratio_sub_checked_impl : public traits::identity<typename ratio_sub_impl<R1, R2>::type> {
            static_assert(is_ratio<R1>::value, "R1 must be of ratio type");
            static_assert(is_ratio<R2>::value, "R2 must be of ratio type");
        };
    }

    template<typename R1, typename R2>
    using ratio_sub [[maybe_unused]] = typename impl::ratio_sub_checked_impl<R1, R2>::type;

    template<typename R1, typename R2>
    struct ratio_equal : public traits::bool_constant<R1::num == R2::num && R1::den == R2::den> {
    };

    template<typename R1, typename R2>
    [[maybe_unused]] inline constexpr auto ratio_equal_v{ratio_equal<R1, R2>::value};

    template<typename R1, typename R2>
    struct ratio_not_equal : public traits::impl::invert_bool_constant_t<ratio_equal<R1, R2>> {
    };

    template<typename R1, typename R2>
    [[maybe_unused]] inline constexpr auto ratio_not_equal_v{ratio_not_equal<R1, R2>::value};

    namespace impl {

        template<typename R1, typename R2,
                std::intmax_t Quot1 = R1::num / R1::den,
                std::intmax_t Rem1 = R1::num % R1::den,
                std::intmax_t Quot2 = R2::num / R2::den,
                std::intmax_t Rem2 = R2::num % R2::den>
        struct ratio_less_base : public traits::bool_constant<Quot1 < Quot2> {
        };

        // Whole fraction with same resulting quotient, so equal fractions.
        template<typename R1, typename R2, std::intmax_t Quot>
        struct ratio_less_base<R1, R2, Quot, 0, Quot, 0> : public traits::bool_constant<false> {
        };

        // Same quotient, but R2 has a remainder, hence R1 < R2
        template<typename R1, typename R2, std::intmax_t Quot, std::intmax_t Rem>
        struct ratio_less_base<R1, R2, Quot, 0, Quot, Rem> : public traits::bool_constant<true> {
        };

        template<typename R1, typename R2, std::intmax_t Quot, std::intmax_t Rem>
        struct ratio_less_base<R1, R2, Quot, Rem, Quot, 0> : public traits::bool_constant<false> {
        };

        template<typename R1, typename R2, std::intmax_t Quot, std::intmax_t Rem1, std::intmax_t Rem2>
        struct ratio_less_base<R1, R2, Quot, Rem1, Quot, Rem2> : public ratio_less_base<ratio<R2::den, Rem2>,
                ratio<R1::den, Rem1>> {
        };

        template<typename R1, typename R2,
                std::intmax_t S1 = static_sign<R1::num>::value,
                std::intmax_t S2 = static_sign<R2::num>::value>
        struct ratio_less_impl : public traits::bool_constant<S1 < S2> {
        };

        template<typename R1, typename R2>
        struct ratio_less_impl<R1, R2, 1LL, 1LL> : public ratio_less_base<R1, R2> {
        };

        template<typename R1, typename R2>
        struct ratio_less_impl<R1, R2, -1LL, -1LL> : public ratio_less_base<
                ratio<-R2::num, R2::den>,
                ratio<-R1::num, R1::den>> {
        };
    };

    template<typename R1, typename R2>
    struct ratio_less : public impl::ratio_less_impl<R1, R2> {
    };

    template<typename R1, typename R2>
    [[maybe_unused]] inline constexpr auto ratio_less_v{ratio_less<R1, R2>::value};

    template<typename R1, typename R2>
    struct ratio_less_equal : public traits::bool_constant<!ratio_less<R2, R1>::value> {
    };

    template<typename R1, typename R2>
    [[maybe_unused]] inline constexpr auto ratio_less_equal_v{ratio_less_equal<R1, R2>::value};

    template<typename R1, typename R2>
    struct ratio_greater : public ratio_less<R2, R1> {
    };

    template<typename R1, typename R2>
    [[maybe_unused]] inline constexpr auto ratio_greater_v{ratio_greater<R1, R2>::value};

    template<typename R1, typename R2>
    struct ratio_greater_equal : public traits::bool_constant<!ratio_less<R1, R2>::value> {
    };

    template<typename R1, typename R2>
    [[maybe_unused]] inline constexpr auto ratio_greater_equal_v{ratio_greater_equal<R1, R2>::value};

    using atto [[maybe_unused]] = ratio<1LL, 1000000000000000000LL>;
    using femto  [[maybe_unused]] = ratio<1LL, 1000000000000000LL>;
    using pico [[maybe_unused]] = ratio<1LL, 1000000000000LL>;
    using nano [[maybe_unused]] = ratio<1LL, 1000000000LL>;
    using micro [[maybe_unused]] = ratio<1LL, 1000000LL>;
    using milli [[maybe_unused]] = ratio<1LL, 1000LL>;
    using centi [[maybe_unused]] = ratio<1LL, 100LL>;
    using deci [[maybe_unused]] = ratio<1LL, 10LL>;
    using deca [[maybe_unused]] = ratio<10LL, 1LL>;
    using hecto [[maybe_unused]] = ratio<100LL, 1LL>;
    using kilo [[maybe_unused]] = ratio<1000LL, 1LL>;
    using mega [[maybe_unused]] = ratio<1000000LL, 1LL>;
    using giga [[maybe_unused]] = ratio<1000000000LL, 1LL>;
    using tera [[maybe_unused]] = ratio<1000000000000LL, 1LL>;
    using peta [[maybe_unused]] = ratio<1000000000000000LL, 1LL>;
    using exa [[maybe_unused]] = ratio<1000000000000000000LL, 1LL>;
}

#endif //RATIO_HPP
