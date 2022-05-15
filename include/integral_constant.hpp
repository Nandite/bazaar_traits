//
// Created by chazz on 09/05/22.
//

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

    template<typename Tp> struct not_bool_constant : public bool_constant<!bool(Tp::value)> {};
    template<> struct not_bool_constant<true_type> : public false_type {};
    template<> struct not_bool_constant<false_type> : public true_type {};

    template<typename Tp>
    using not_bool_constant_t = typename not_bool_constant<Tp>::type;
    template<typename Tp>
    static constexpr bool not_bool_constant_v = not_bool_constant<Tp>::value;
}