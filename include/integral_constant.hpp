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

    namespace impl {
        template<typename Tp>
        struct invert_bool_constant : public bool_constant<!bool(Tp::value)> {};
        template<typename Tp>
        using invert_bool_constant_t = typename invert_bool_constant<Tp>::type;
    }
}