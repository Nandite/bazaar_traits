//
// Created by chazz on 15/05/22.
//

#ifndef BAZAAR_LOGICAL_OPERATORS_HPP
#define BAZAAR_LOGICAL_OPERATORS_HPP

#include "helper_traits.hpp"

namespace bazaar::traits
{
    //------------------------ [meta.logical], logical operator traits ---------------------

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
    namespace impl
    {
        template<typename B>
        struct negation_impl : public not_bool_constant_t<B> {};
    }

    template<typename B>
    struct negation : public impl::negation_impl<B>{};

    template<typename B>
    [[maybe_unused]] inline constexpr auto negation_v {negation<B>::value};
}

#endif //BAZAAR_LOGICAL_OPERATORS_HPP
