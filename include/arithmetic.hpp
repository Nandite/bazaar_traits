//
// Created by chazz on 10/05/22.
//

#pragma once
#include <cstddef>
#include "integral_constant.hpp"

namespace bazaar::traits
{
    // Max
    namespace impl {
        template<std::size_t I0, std::size_t ... In>
        struct meta_max {
        };

        template<std::size_t I0>
        struct meta_max<I0> {
            static constexpr std::size_t value = I0;
        };

        template<std::size_t I0, std::size_t I1, std::size_t ... In>
        struct meta_max<I0, I1, In...> {
            static constexpr std::size_t value = I0 > I1 ? meta_max<I0, In...>::value : meta_max<I1, In...>::value;
        };
    }

    template<std::size_t I0, std::size_t I1, std::size_t ... In>
    inline constexpr std::size_t meta_max_v = impl::meta_max<I0, I1, In...>::value;

    // Min
    namespace impl {
        template<std::size_t I0, std::size_t  ... In>
        struct meta_min {
        };

        template<std::size_t I0>
        struct meta_min<I0> {
            static constexpr std::size_t value = I0;
        };

        template<std::size_t I0, std::size_t I1, std::size_t ... In>
        struct meta_min<I0, I1, In...> {
            static constexpr std::size_t value = I0 < I1 ? meta_min<I0, In...>::value : meta_min<I1, In...>::value;
        };
    }

    template<std::size_t I0, std::size_t I1, std::size_t ... In>
    inline constexpr std::size_t meta_min_v = impl::meta_min<I0, I1, In...>::value;

    // Integral and floating points
    namespace impl
    {
        template<typename Tp> struct is_integral_impl : public false_type {};
        template<> struct is_integral_impl<bool> : public true_type {};
        template<> struct is_integral_impl<char> : public true_type {};
        template<> struct is_integral_impl<signed char> : public true_type {};
        template<> struct is_integral_impl<unsigned char> : public true_type {};
        template<> struct is_integral_impl<wchar_t> : public true_type {};
        template<> struct is_integral_impl<char16_t> : public true_type {};
        template<> struct is_integral_impl<char32_t> : public true_type {};
        template<> struct is_integral_impl<short> : public true_type {};
        template<> struct is_integral_impl<unsigned short> : public true_type {};
        template<> struct is_integral_impl<int> : public true_type {};
        template<> struct is_integral_impl<unsigned int> : public true_type {};
        template<> struct is_integral_impl<long> : public true_type {};
        template<> struct is_integral_impl<unsigned long> : public true_type {};
        template<> struct is_integral_impl<long long> : public true_type {};
        template<> struct is_integral_impl<unsigned long long> : public true_type {};

        template<typename Tp> struct is_floating_point_impl : public false_type {};
        template<> struct is_floating_point_impl<float> : public true_type {};
        template<> struct is_floating_point_impl<double> : public true_type {};
        template<> struct is_floating_point_impl<long double> : public true_type {};

        template<typename Tp> struct is_signed_integer_impl : public false_type{};
        template<> struct is_signed_integer_impl<signed char> : public true_type{};
        template<> struct is_signed_integer_impl<signed short> : public true_type{};
        template<> struct is_signed_integer_impl<signed int> : public true_type{};
        template<> struct is_signed_integer_impl<signed long> : public true_type{};
        template<> struct is_signed_integer_impl<signed long long> : public true_type{};

        template<typename Tp> struct is_unsigned_integer_impl : public false_type{};
        template<> struct is_unsigned_integer_impl<unsigned char> : public true_type{};
        template<> struct is_unsigned_integer_impl<unsigned short> : public true_type{};
        template<> struct is_unsigned_integer_impl<unsigned int> : public true_type{};
        template<> struct is_unsigned_integer_impl<unsigned long> : public true_type{};
        template<> struct is_unsigned_integer_impl<unsigned long long> : public true_type{};
    }


}
