//
// Created by user on 09/09/2022.
//

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

        template<std::intmax_t X, std::intmax_t Y>
        struct static_lcm : public traits::integral_constant<std::intmax_t, X * Y / static_gcd<X, Y>::value> {
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
        class overflow_checked_mul;

        template<std::intmax_t X, std::intmax_t Y>
        class overflow_checked_mul<X, Y, false> : public overflow_arithmetic {
            constexpr static std::intmax_t xAbs{static_abs<X>::value};
            constexpr static std::intmax_t yAbs{static_abs<Y>::value};
            static_assert(X != nan && Y != nan && xAbs <= (max / yAbs), "overflow occurred during multiplication");
        public:
            constexpr static std::intmax_t value{X * Y};
        };

        template<std::intmax_t X, std::intmax_t Y>
        class overflow_checked_mul<X, Y, true> {
        public:
            constexpr static std::intmax_t value{0};
        };

        template<std::intmax_t X, std::intmax_t Y>
        class overflow_checked_div : public overflow_arithmetic {
            static_assert(X != nan && Y != nan && Y != 0, "overflow occurred during division");
        public:
            constexpr static std::intmax_t value{X / Y};
        };
    }

    template<std::intmax_t Num, std::intmax_t Den = 1>
    class ratio {
        static_assert(impl::static_abs<Num>::value >= 0, "Numerator value is out of range");
        static_assert(Den != 0, "Trying to divide by zero");
        static_assert(impl::static_abs<Den>::value > 0, "Denominator value is out of range");
        constexpr static std::intmax_t gcd{impl::static_gcd<Num, Den>::value};
        constexpr static std::intmax_t sa{impl::static_sign<Num>::value};
        constexpr static std::intmax_t sd{impl::static_sign<Den>::value};
        constexpr static std::intmax_t na{impl::static_abs<Num>::value};
        constexpr static std::intmax_t da{impl::static_abs<Den>::value};
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
        template<typename R1, typename R2>
        class ratio_multiply_impl {
            constexpr static std::intmax_t gcdN1D2{static_gcd<R1::num, R2::den>::value};
            constexpr static std::intmax_t gcdN2D1{static_gcd<R2::num, R1::den>::value};
        public:
            using type = typename ratio<overflow_checked_mul<R1::num / gcdN1D2, R2::num / gcdN2D1>::value,
                    overflow_checked_mul<R1::den / gcdN2D1, R2::den / gcdN1D2>::value>::type;
        };

        template<typename R1, typename R2>
        class ratio_multiply_checked_impl : public traits::identity<
                typename ratio_multiply_impl<R1, R2>::type
        > {
            static_assert(is_ratio<R1>::value, "R1 must be of ratio type");
            static_assert(is_ratio<R2>::vaue, "R2 must be of ratio type");
        };
    }

    template<typename R1, typename R2>
    using ratio_multiply [[maybe_unused]] = typename impl::ratio_multiply_checked_impl<R1, R2>::type;

    namespace impl {

        template<typename R1, typename R2>
        class ratio_divide_impl {
            constexpr static std::intmax_t gcdN1D2{static_gcd<R1::num, R2::den>::value};
            constexpr static std::intmax_t gcdN2D1{static_gcd<R2::num, R1::den>::value};
        public:
            using type = typename ratio<overflow_checked_mul<R1::num / gcdN1D2, R2::den / gcdN1D2>::value,
                    overflow_checked_mul<R1::den / gcdN2D1, R2::num / gcdN2D1>::value>::type;
        };

        template<typename R1, typename R2>
        class ratio_divide_checked_impl : public traits::identity<
                typename ratio_divide_impl<R1, R2>::type
        > {
            static_assert(is_ratio<R1>::value, "R1 must be of ratio type");
            static_assert(is_ratio<R2>::vaue, "R2 must be of ratio type");
        };
    }

    template<typename R1, typename R2>
    using ratio_divide [[maybe_unused]] = typename impl::ratio_multiply_checked_impl<R1, R2>::type;

    namespace impl
    {
        
    }

    using atto = ratio<1LL, 1000000000000000000LL>;
    using femto = ratio<1LL, 1000000000000000LL>;
    using pico = ratio<1LL, 1000000000000LL>;
    using nano = ratio<1LL, 1000000000LL>;
    using micro = ratio<1LL, 1000000LL>;
    using milli = ratio<1LL, 1000LL>;
    using centi = ratio<1LL, 100LL>;
    using deci = ratio<1LL, 10LL>;
    using deca = ratio<10LL, 1LL>;
    using hecto = ratio<100LL, 1LL>;
    using kilo = ratio<1000LL, 1LL>;
    using mega = ratio<1000000LL, 1LL>;
    using giga = ratio<1000000000LL, 1LL>;
    using tera = ratio<1000000000000LL, 1LL>;
    using peta = ratio<1000000000000000LL, 1LL>;
    using exa = ratio<1000000000000000000LL, 1LL>;
}

#endif //RATIO_HPP
