//
// Created by chazz on 10/05/22.
//

#pragma once
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
