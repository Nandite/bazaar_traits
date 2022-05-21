//
// Created by chazz on 09/05/22.
//

#pragma once

#include "logical_operators.hpp"
#include "type_list.hpp"

namespace bazaar::traits {

    //-------------------------------------------------------------------------------------------
    // Array properties and transformations
    //-------------------------------------------------------------------------------------------

    // Rank
    namespace impl
    {
        template<typename Tp> struct rank_impl : integral_constant<std::size_t ,0>{};
        template<typename Tp> struct rank_impl<Tp[]> : integral_constant< std::size_t,
                1 + rank_impl<Tp>::value>{};
        template<typename Tp, std::size_t N> struct rank_impl<Tp[N]> : integral_constant<std::size_t,
                1 + rank_impl<Tp>::value>{};
    }

    template<typename Tp> struct rank : public impl::rank_impl<Tp>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto rank_v{rank<Tp>::value};

    // Extent
    namespace impl {
        template<typename Tp, std::size_t N = 0>
        struct extent_impl : public integral_constant<std::size_t, 0>{};

        template<typename Tp>
        struct extent_impl<Tp[], 0> : public integral_constant<std::size_t, 0>{};

        template<typename Tp, std::size_t Dim>
        struct extent_impl<Tp[], Dim> : public extent_impl<Tp, Dim-1>{};

        template<typename Tp, std::size_t Dim>
        struct extent_impl<Tp[Dim], 0> : public integral_constant<std::size_t, Dim>{};

        template<typename Tp, std::size_t Dim, std::size_t N>
        struct extent_impl<Tp[Dim], N> : public extent_impl<Tp, N - 1>{};
    }

    template<typename Tp, std::size_t N = 0>
    struct extent : public impl::extent_impl<Tp, N>{};

    template<typename Tp, std::size_t N = 0>
    [[maybe_unused]] inline constexpr auto extent_v{extent<Tp, N>::value};

    // Remove extent
    template<typename Tp> struct remove_extent : public identity<Tp>{};
    template<typename Tp> struct remove_extent<Tp[]> : public identity<Tp>{};
    template<typename Tp, std::size_t N>
    struct remove_extent<Tp[N]> : public identity<Tp>{};

    template<typename Tp>
    using remove_extent_t [[maybe_unused]] = typename remove_extent<Tp>::type;

    // Remove all extents
    template<typename Tp> struct remove_all_extents : public identity<Tp>{};
    template<typename Tp>
    struct remove_all_extents<Tp[]> : public identity<typename remove_all_extents<Tp>::type>{};
    template<typename Tp, std::size_t N>
    struct remove_all_extents<Tp[N]> : public identity<typename remove_all_extents<Tp>::type> {};

    template<typename Tp>
    using remove_all_extents_t [[maybe_unused]] = typename remove_all_extents<Tp>::type;

    namespace impl {
        template<typename Tp> struct is_bounded_array_impl : public false_type {};
        template<typename Tp, std::size_t N> struct is_bounded_array_impl<Tp[N]> : public true_type {};
        template<typename Tp> struct is_unbounded_array_impl : public false_type {};
        template<typename Tp> struct is_unbounded_array_impl<Tp[]> : public true_type {};
    }

    template<typename Tp>
    struct is_bounded_array : public impl::is_bounded_array_impl<Tp>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_bounded_array_v{is_bounded_array<Tp>::value};

    template<typename Tp>
    struct is_unbounded_array : public impl::is_unbounded_array_impl<Tp>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_unbounded_array_v{is_unbounded_array<Tp>::value};

    //-------------------------------------------------------------------------------------------
    // Reference transformations
    //-------------------------------------------------------------------------------------------

    // Remove reference
    template<typename Tp> struct remove_reference : public identity<Tp>{};
    template<typename Tp> struct remove_reference<Tp&> : public identity<Tp>{};
    template<typename Tp> struct remove_reference<Tp&&> : public identity<Tp>{};

    template<typename Tp>
    using remove_reference_t [[maybe_unused]] = typename remove_reference<Tp>::type;

    namespace impl
    {
        // Is referenceable
        struct is_non_referenceable_type;
        template<typename Tp> Tp& test_is_referenceable(int);
        template<typename> is_non_referenceable_type test_is_referenceable(...);
        template<typename Tp>
        struct is_referenceable
                : public bool_condition<is_not_same_v<is_non_referenceable_type,
                        decltype(test_is_referenceable<Tp>(0))>>::type {
        };
    }

    // Add lvalue reference
    namespace impl {
        template<typename Tp, bool = impl::is_referenceable<Tp>::value>
        struct add_lvalue_reference_impl : public identity<Tp>{};
        template<typename Tp> struct add_lvalue_reference_impl<Tp, true> : public identity<Tp&>{};
    }

    template<typename Tp>
    struct add_lvalue_reference : public identity<typename impl::add_lvalue_reference_impl<Tp>::type> {};

    template<typename Tp>
    using add_lvalue_reference_t [[maybe_unused]] = typename add_lvalue_reference<Tp>::type;

    // Add rvalue reference
    namespace impl {
        template<typename Tp, bool = impl::is_referenceable<Tp>::value>
        struct add_rvalue_reference_impl : public identity<Tp>{};
        template<typename Tp> struct add_rvalue_reference_impl<Tp, true> : public identity<Tp&&>{};
    }

    template<typename Tp>
    struct add_rvalue_reference : public identity<typename impl::add_rvalue_reference_impl<Tp>::type> {};

    template<typename Tp>
    using add_rvalue_reference_t [[maybe_unused]] = typename add_rvalue_reference<Tp>::type;

    //-------------------------------------------------------------------------------------------
    // Const-volatile properties and transformations
    //-------------------------------------------------------------------------------------------

    // Is const
    template<typename Tp> struct is_const : public false_type {};
    template<typename Tp> struct is_const<Tp const> : public true_type {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_const_v {is_const<Tp>::value};

    // Is volatile
    template<typename Tp> struct is_volatile : public false_type {};
    template<typename Tp> struct is_volatile<Tp volatile> : public true_type {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_volatile_v{is_volatile<Tp>::value};

    // Remove const
    template <typename Tp> struct remove_const : public identity<Tp>{};
    template <typename Up> struct remove_const<const Up> : public identity<Up>{};
    template<typename Tp> using remove_const_t = typename remove_const<Tp>::type ;

    // Remove volatile
    template <typename Tp> struct remove_volatile : public identity<Tp>{};
    template <typename Up> struct remove_volatile<volatile Up> : public identity<Up>{};
    template<typename Tp> using remove_volatile_t = typename remove_volatile<Tp>::type ;

    // Remove cv
    template<typename Tp>
    struct remove_cv : public identity<remove_const_t<remove_volatile_t<Tp>>>{};
    template<typename Tp> using remove_cv_t = typename remove_cv<Tp>::type;

    // Add const
    template<typename Tp>
    struct add_const : public identity<const Tp>{};
    template<typename Tp>
    using add_const_t = typename add_const<Tp>::type;

    // Add volatile
    template<typename Tp>
    struct add_volatile : public identity<volatile Tp>{};
    template<typename Tp>
    using add_volatile_t = typename add_volatile<Tp>::type;

    // Add cv
    template<typename Tp>
    struct add_cv : public identity<add_const_t<add_volatile_t<Tp>>> {};
    template<typename Tp>
    using add_cv_t [[maybe_unused]] = typename add_cv<Tp>::type;

    // Apply cv
    namespace impl
    {
        template<typename In, typename Out, bool = is_const_v<remove_reference_t<In>>,
                bool = is_volatile_v<remove_reference_t<In>>>
        struct apply_cv_impl : public identity<Out> {};

        template<typename In, typename Out>
        struct apply_cv_impl<In, Out, true, false> : public identity<const Out>{};

        template<typename In, typename Out>
        struct apply_cv_impl<In, Out, false, true> : public identity<volatile Out>{};

        template<typename In, typename Out>
        struct apply_cv_impl<In, Out, true, true> : public identity<const volatile Out>{};

        template<typename In, typename Out>
        struct apply_cv_impl<In&, Out, false, false> : public identity<Out&>{};

        template<typename In, typename Out>
        struct apply_cv_impl<In&, Out, true, false> : public identity<const Out&>{};

        template<typename In, typename Out>
        struct apply_cv_impl<In&, Out, false, true> : public identity<volatile Out&>{};

        template<typename In, typename Out>
        struct apply_cv_impl<In&, Out, true, true> : public identity<const volatile Out&>{};
    }

    template<typename In, typename Out>
    struct apply_cv : public impl::apply_cv_impl<In, Out> {};

    template<typename In, typename Out>
    using apply_cv_t [[maybe_unused]] = typename apply_cv<In,Out>::type;

    //-------------------------------------------------------------------------------------------
    // Primary classification traits
    //-------------------------------------------------------------------------------------------

    // Is void
    template<typename Tp>
    struct is_void : public is_one_of<Tp, void, void const, void volatile, void const volatile>{};

    // Alternate
    //    template<typename Tp>
    //    struct [[maybe_unused]] is_void {
    //        static constexpr bool value = is_same_v<std::remove_cv_t<Tp>, void>
    //                                      || is_same_v<std::remove_cv_t<Tp>, void const>
    //                                      || is_same_v<std::remove_cv_t<Tp>, void volatile> ||
    //                                      is_same_v<std::remove_cv_t<Tp>, void const volatile>;
    //    };

    // Alternate
    //    template<typename Tp>
    //    struct [[maybe_unused]] is_void : public is_same<remove_cv_t<Tp>, void>::type {};

    // Alternate
    //        template<typename Tp> struct [[maybe_unused]] is_void : public false_type {};
    //        template<> struct [[maybe_unused]] is_void<void> : public true_type {};
    //        template<> struct [[maybe_unused]] is_void<void const> : public true_type {};
    //        template<> struct [[maybe_unused]] is_void<void volatile> : public true_type {};
    //        template<> struct [[maybe_unused]] is_void<void const volatile> : public true_type {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr bool is_void_v = is_void<Tp>::value;

    // Is nullptr
    namespace impl {
        template<typename Tp>
        struct is_null_pointer_impl {static constexpr bool value{is_same_v<remove_cv_t<Tp>, nullptr_t>};};

        // Alternate
        //    template<typename Tp>
        //    struct is_null_pointer_impl : public is_same<remove_cv_t<Tp>, nullptr_t>::type{};
    }

    template<typename Tp>
    struct is_null_pointer : public impl::is_null_pointer_impl<Tp>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr bool is_null_pointer_v = is_null_pointer<Tp>::value;

    // Is integral and floating
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

    template<typename Tp>
    struct is_integral : public impl::is_integral_impl<remove_cv_t<Tp>> {};
    template<typename Tp>
    [[maybe_unused]] inline constexpr bool is_integral_v = is_integral<Tp>::value;

    template<typename Tp>
    struct is_floating_point : public impl::is_floating_point_impl<remove_cv_t<Tp>> {};
    template<typename Tp>
    [[maybe_unused]] inline constexpr bool is_floating_v = is_floating_point<Tp>::value;

    template<typename Tp>
    struct is_signed_integer : public conjunction<is_integral<remove_cv_t<Tp>>,
            impl::is_signed_integer_impl<remove_cv_t<Tp>>>{};
    template<typename Tp>
    [[maybe_unused]] inline constexpr bool is_signed_integer_v = is_signed_integer<Tp>::value;

    template<typename Tp>
    struct is_unsigned_integer : public conjunction<is_integral<remove_cv_t<Tp>>,
            impl::is_unsigned_integer_impl<remove_cv_t<Tp>>>{};
    template<typename Tp>
    [[maybe_unused]] inline constexpr bool is_unsigned_integer_v = is_unsigned_integer<Tp>::value;

    // Is arithmetic
    template<typename Tp>
    struct is_arithmetic : public is_true_one_of<typename is_integral<Tp>::type,
            typename is_floating_point<Tp>::type>{};

    // Alternate
    // template<typename Tp>
    // struct is_arithmetic : public bool_constant<is_integral_v<Tp> || is_floating_v<Tp>>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_arithmetic_v {is_arithmetic<Tp>::value};

    // Is array
    template<typename Tp> struct is_array : public false_type {};
    template<typename Tp> struct is_array<Tp[]> : public true_type {};
    template<typename Tp, std::size_t N> struct is_array<Tp[N]> : public true_type {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr bool is_array_v = is_array<Tp>::value;

    // Is pointer
    template<typename Tp> struct is_pointer : public false_type {};
    template<typename Tp> struct is_pointer<Tp*> : public true_type {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_pointer_v{is_pointer<Tp>::value};

    // Is lvalue  reference
    template<typename Tp> struct is_lvalue_reference : public false_type {};
    template<typename Tp> struct is_lvalue_reference<Tp&> : public true_type {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_lvalue_reference_v = is_lvalue_reference<Tp>::value;

    // Is rvalue reference
    template<typename Tp> struct is_rvalue_reference : public false_type {};
    template<typename Tp> struct is_rvalue_reference<Tp&&> : public true_type {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_rvalue_reference_v = is_rvalue_reference<Tp>::value;

    // Is reference
    template<typename Tp>
    struct is_reference : public disjunction<is_lvalue_reference<Tp>, is_rvalue_reference<Tp>> {};

    // Alternate
//    template<typename Tp> struct is_reference : public false_type {};
//    template<typename Tp> struct is_reference<Tp&> : public true_type {};
//    template<typename Tp> struct is_reference<Tp&&> : public true_type {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_reference_v = is_reference<Tp>::value;

    // Is function
    template<typename Tp>
    struct is_function : public negation<
            disjunction<is_const<Tp>, is_reference<Tp>>>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_function_v {is_function<Tp>::value};

    // Is member pointer
    namespace impl
    {
        template<typename Tp>
        struct is_member_pointer_impl : public false_type {};

        template<typename Tp, typename Up>
        struct is_member_pointer_impl<Tp Up::*> : public true_type {};
    }

    template<typename Tp>
    struct is_member_pointer : public impl::is_member_pointer_impl<Tp>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_member_pointer_v{is_member_pointer<Tp>::value};

    // Is member object pointer
    template<typename Tp>
    struct is_member_object_pointer : public conjunction<
            is_member_pointer<Tp>,
            negation<is_function<Tp>>
            >{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_member_object_pointer_v {is_member_object_pointer<Tp>::value};

    // Is member function pointer
    template<typename Tp>
    struct is_member_function_pointer : public conjunction<
            is_member_pointer<Tp>,
            is_function<Tp>>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_member_function_pointer_v {is_member_function_pointer<Tp>::value};

    // Is member union
#if (__has_feature(is_union) || defined(_LIBCPP_COMPILER_GCC))
    template <typename Tp> struct is_union : public bool_constant<__is_union(Tp)> {};
#else
    template <typename Tp> struct is_union_impl : public false_type {};
    template <typename Tp> struct is_union : public is_union_impl<remove_cv_t<Tp>> {};
#endif
    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_union_v{is_union<Tp>::value};

    // Is class
#if (__has_feature(is_class) || defined(_LIBCPP_COMPILER_GCC))
    template<typename Tp> struct is_class : public bool_constant<__is_class(Tp)>{};
#else
    namespace impl
    {
        struct is_not_class_type {};
        template<typename Tp, typename = void_t<int Tp::*>> true_type is_class_test(int);
        template<typename> is_not_class_type is_class_test(...);
    }
    template<typename Tp> struct is_class : public
            is_not_same<decltype(impl::is_class_test<Tp>(0)), impl::is_not_class_type>{};
#endif

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_class_v{is_class<Tp>::value};

    // Is enum
#if (__has_feature(is_enum) || defined(_LIBCPP_COMPILER_GCC))
    template<typename Tp> struct is_enum : public bool_constant<__is_enum(Tp)>{};
#else
    template<typename Tp> struct is_enum : public negation<disjunction<
                                is_void<Tp>,
                                is_arithmetic<Tp>,
                                is_array<Tp>,
                                is_pointer<Tp>,
                                is_reference<Tp>,
                                is_member_pointer<Tp>,
                                is_union<Tp>,
                                is_class<Tp>,
                                is_function<Tp>>>{};
#endif

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_enum_v{is_enum<Tp>::value};

    //-------------------------------------------------------------------------------------------
    // Secondary classification traits
    //-------------------------------------------------------------------------------------------

    // Is fundamental
    template<typename Tp>
    struct is_fundamental : public disjunction<
                is_arithmetic<Tp>,
                is_void<Tp>,
                is_null_pointer<Tp>>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_fundamental_v {is_fundamental<Tp>::value};

    // Is scalar
    template<typename Tp>
    struct is_scalar : public disjunction<
            is_arithmetic<Tp>,
            is_pointer<Tp>,
            is_member_pointer<Tp>,
            is_enum<Tp>,
            is_null_pointer<Tp>
            // Case when Tp is an objective-C++ block is not handled
            > {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_scalar_v {is_scalar<Tp>::value};

    // Is object
    template<typename Tp>
    struct is_object : public conjunction<
                negation<is_reference<Tp>>,
                negation<is_function<Tp>>,
                negation<is_void<Tp>>>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_object_v {is_object<Tp>::value};

    //Is compound
    template<typename Tp>
    struct is_compound : public negation<is_fundamental<Tp>> {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_compound_v{is_compound<Tp>::value};

    //-------------------------------------------------------------------------------------------
    // Pointer transformations
    //-------------------------------------------------------------------------------------------

    // Remove pointer
    namespace impl
    {
        template<typename Tp> struct remove_pointer_helper : public identity<Tp>{};
        template<typename Tp> struct remove_pointer_helper<Tp*> : public identity<Tp>{};
        template<typename Tp, bool = is_pointer_v<Tp>> struct remove_pointer_impl : public identity<Tp> {};
        template<typename Tp>
        struct remove_pointer_impl<Tp, true> : public identity<typename remove_pointer_helper<Tp>::type> {};
    }

    // Alternate
    // template<typename Tp> struct remove_pointer : identity<Tp> {};
    // template<typename Tp> struct remove_pointer<Tp*> : identity<Tp> {};
    // template<typename Tp> struct remove_pointer<Tp* const> : identity<Tp> {};
    // template<typename Tp> struct remove_pointer<Tp * volatile> : identity<Tp> {};
    // template<typename Tp> struct remove_pointer<Tp * const volatile> : identity<Tp> {};

    template<typename Tp>
    struct remove_pointer : public impl::remove_pointer_impl<remove_cv_t<Tp>> {};

    template<typename Tp>
    using remove_pointer_t [[maybe_unused]] = typename remove_pointer<Tp>::type;

    // Add pointer
    namespace impl
    {
        template<typename Tp, bool = is_referenceable<Tp>::value || is_void_v<Tp>>
        struct add_pointer_impl   : public identity<remove_reference_t<Tp>*>{};

        template<typename Tp>
        struct add_pointer_impl<Tp, false> : public identity<Tp>{};
    }

    template<typename Tp>
    struct add_pointer : public impl::add_pointer_impl<Tp>{};

    template<typename Tp>
    using add_pointer_t [[maybe_unused]] = typename add_pointer<Tp>::type;

    //-------------------------------------------------------------------------------------------
    // Integral properties
    //-------------------------------------------------------------------------------------------

    // Is signed
    namespace impl
    {
        template<typename Tp, bool = is_integral_v<Tp>>
        struct is_signed_impl  : public bool_condition<Tp(-1) < Tp(0)>{};

        template<typename Tp> // floating point is signed by default
        struct is_signed_impl<Tp, false> : public true_type {};
    }

    template<typename Tp, bool = is_arithmetic_v<Tp>>
    struct is_signed : public impl::is_signed_impl<Tp>{};

    template<typename Tp>
    struct is_signed<Tp, false> : public false_type {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_signed_v {is_signed<Tp>::value};

    // Is unsigned
    namespace impl
    {
        template<typename Tp, bool = is_integral_v<Tp>>
        struct is_unsigned_impl  : public bool_condition<Tp(0) < Tp(-1)>{};

        template<typename Tp> // floating point is signed by default
        struct is_unsigned_impl<Tp, false> : public false_type {};
    }

    template<typename Tp, bool = is_arithmetic_v<Tp>>
    struct is_unsigned : public impl::is_unsigned_impl<Tp>{};

    template<typename Tp>
    struct is_unsigned<Tp, false> : public false_type {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_unsigned_v {is_unsigned<Tp>::value};

    // Make signed
    namespace impl
    {
        template<typename Tp, bool = is_integral_v<Tp> || is_enum_v<Tp>>
        struct make_signed_impl {};

        template<typename Tp>
        struct make_signed_impl<Tp, true> : public identity<
                typename impl::find_first_upper_bound_element_by_size<signed_types_list, sizeof(Tp)>::type
                > {};

        template<> struct make_signed_impl <bool, true> {};
        template<> struct make_signed_impl <signed short, true> : public identity<short>{};
        template<> struct make_signed_impl <unsigned short, true> : public identity<short>{};
        template<> struct make_signed_impl <signed int, true> : public identity<int>{};
        template<> struct make_signed_impl <unsigned int, true> : public identity<int>{};
        template<> struct make_signed_impl <signed long, true> : public identity<long>{};
        template<> struct make_signed_impl <unsigned long, true> : public identity<long>{};
        template<> struct make_signed_impl <signed long long, true> : public identity<long long>{};
        template<> struct make_signed_impl <unsigned long long, true> : public identity<long long>{};
    }

    template<typename Tp>
    struct make_signed : identity<typename apply_cv<Tp,
            impl::make_signed_impl<remove_cv_t<Tp>>>::type> {};

    template<typename Tp>
    using make_signed_t [[maybe_unused]] = typename make_signed<Tp>::type;

    // Make unsigned
    namespace impl
    {
        template<typename Tp, bool = is_integral_v<Tp> || is_enum_v<Tp>>
        struct make_unsigned_impl {};

        template<typename Tp>
        struct make_unsigned_impl<Tp, true> : public identity<
                typename impl::find_first_upper_bound_element_by_size<unsigned_types_list,
                sizeof(Tp)>::type
        > {};

        template<> struct make_unsigned_impl <bool, true> {};
        template<> struct make_unsigned_impl <signed short, true> : public identity<short>{};
        template<> struct make_unsigned_impl <unsigned short, true> : public identity<short>{};
        template<> struct make_unsigned_impl <signed int, true> : public identity<int>{};
        template<> struct make_unsigned_impl <unsigned int, true> : public identity<int>{};
        template<> struct make_unsigned_impl <signed long, true> : public identity<long>{};
        template<> struct make_unsigned_impl <unsigned long, true> : public identity<long>{};
        template<> struct make_unsigned_impl <signed long long, true> : public identity<long long>{};
        template<> struct make_unsigned_impl <unsigned long long, true> : public identity<long long>{};
    }

    template<typename Tp>
    struct make_unsigned : identity<typename apply_cv<Tp,
            impl::make_unsigned_impl<remove_cv_t<Tp>>>::type> {};

    template<typename Tp>
    using make_unsigned_t [[maybe_unused]] = typename make_unsigned<Tp>::type;

    //-------------------------------------------------------------------------------------------
    // Member introspection
    //-------------------------------------------------------------------------------------------

    // Is constructible
    namespace impl
    {
        template<typename Tp, typename ... Args>
        struct is_constructible_impl: public bool_constant<__is_constructible(Tp, Args...)> {};
    }

    template<typename Tp, typename ... Args>
    struct is_constructible : public impl::is_constructible_impl<Tp, Args...> {};

    template<typename Tp, typename ... Args>
    [[maybe_unused]] inline constexpr auto is_constructible_v = is_constructible<Tp, Args...>::value;

    //Is default constructible
    template<typename Tp>
    struct is_default_constructible : public is_constructible<Tp>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_default_constructible_v = is_default_constructible<Tp>::value;

    // Is copy constructible
    template<typename Tp>
    struct is_copy_constructible : public is_constructible<Tp,
                add_lvalue_reference_t<add_const_t<Tp>>>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_copy_constructible_v = is_copy_constructible<Tp>::value;

    // Is move constructible
    template<typename Tp>
    struct is_move_constructible : public is_constructible<Tp,
            add_rvalue_reference_t<Tp>>{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_move_constructible_v = is_move_constructible<Tp>::value;


    // Is assignable
    namespace impl {

        template<typename Tp, typename Up>
        using is_assignable_helper_t = decltype(std::declval<Tp>() = std::declval<Up>());

//        template<typename Tp, typename Up, typename = void_t<is_assignable_helper_t<Tp, Up>>>
//        true_type is_assignable_test(int);
//
//        template<typename, typename>
//        false_type is_assignable_test(...);
//
//        template<typename Tp, typename Up, bool = is_void_v<Tp> || is_void_v<Up>>
//        struct is_assignable_impl : public decltype((is_assignable_test<Tp, Up>(0))){};
//
//        template<typename Tp, typename Up>
//        struct is_assignable_impl<Tp, Up, true> : public false_type {};

        template<typename, typename, typename = void>
        struct is_assignable_impl : public false_type {};

        template<typename Tp, typename Up>
        struct is_assignable_impl<Tp, Up, void_t<is_assignable_helper_t<Tp, Up>>> : public is_same<
                is_assignable_helper_t<Tp, Up>, Tp> {};

//        template<typename Tp, typename Up>
//        struct is_assignable_impl
//        {
//        private:
//            template<typename = decltype((std::declval<Tp>() = std::declval<Up>()))>
//            static true_type is_assignable_test(int);
//            static false_type is_assignable_test(...);
//        public:
//            using type = decltype((is_assignable_test(0)));
//        };
    }

    template<typename Tp, typename Up>
    struct is_assignable : public impl::is_assignable_impl<Tp, Up> {};

    template<typename Tp, typename Up>
    [[maybe_unused]] static constexpr bool is_assignable_v = is_assignable<Tp, Up>::value;

    // Is copy assignable
    template<typename Tp>
    struct is_copy_assignable : public is_assignable<add_lvalue_reference_t<Tp>,
            add_const_t<add_lvalue_reference_t<Tp>>>::type {};

    template<typename Tp>
    [[maybe_unused]] static constexpr auto is_copy_assignable_v {is_copy_assignable<Tp>::value};

    // Is move assignable
    template<typename Tp>
    struct is_move_assignable : public is_assignable<add_lvalue_reference_t<Tp>,
            add_rvalue_reference_t<Tp>>::type{};

    template<typename Tp>
    [[maybe_unused]] static constexpr auto is_move_assignable_v{is_move_assignable<Tp>::value};

    // Is swappable with
    namespace impl
    {
        template<typename Tp, typename Up>
        using is_swappable_with_helper_t = decltype(std::swap(std::declval<Tp>(), std::declval<Up>()));

        template<typename , typename, typename = void>
        struct is_swappable_with_impl : public false_type {};

        template<typename Tp, typename Up>
        struct is_swappable_with_impl<Tp, Up, void_t<is_swappable_with_helper_t<Tp, Up>,
                is_swappable_with_helper_t<Up,Tp>>> : public true_type {};
    }

    template<typename Tp, typename Up>
    struct is_swappable_with : public conjunction<
            impl::is_swappable_with_impl<Tp, Up>
            > {};

    template<typename Tp, typename Up>
    [[maybe_unused]] static constexpr auto is_swappable_with_v{is_swappable_with<Tp,Up>::value};

    // Is swappable
    template<typename Tp>
    struct is_swappable : public conjunction<
            impl::is_referenceable<Tp>,
            negation<is_void<Tp>>,
            is_swappable_with<add_lvalue_reference_t<Tp>,
                    add_lvalue_reference_t<Tp>>>{};

    // Alternate
//    template<typename Tp>
//    struct is_swappable : public conditional_t<
//            impl::is_referenceable<Tp>::value && negation_v<is_void<Tp>> ,
//            typename is_swappable_with<add_lvalue_reference_t<Tp>,
//                add_lvalue_reference_t<Tp>>::type,
//            false_type
//            >{};

    template<typename Tp>
    [[maybe_unused]] static constexpr auto is_swappable_v{is_swappable<Tp>::value};

    // Is destructible
    namespace impl
    {
        template<typename Tp>
        using is_destructible_helper_t = decltype(std::declval<Tp&>().~Tp());

        template<typename , typename = void>
        struct is_destructible_impl : public false_type {};

        template<typename Tp>
        struct is_destructible_impl<Tp,
                void_t<is_destructible_helper_t<Tp>>> : public true_type {};
    }

    template<typename Tp>
    struct is_destructible : public disjunction<
            is_reference<Tp>,
            conjunction<
                negation<is_void<Tp>>,
                negation<is_function<Tp>>,
                negation<is_unbounded_array<Tp>>,
                impl::is_destructible_impl<remove_all_extents_t<Tp>>>>{};

    template<typename Tp>
    [[maybe_unused]] static constexpr auto is_destructible_v{is_destructible<Tp>::value};

    // Is trivially constructible
    template<typename Tp, typename ... Args>
    struct is_trivially_constructible : public bool_constant<
            __is_trivially_constructible(Tp, Args...)
            >{};

    template<typename Tp, typename ... Args>
    [[maybe_unused]] static constexpr
    auto is_trivially_constructible_v{is_trivially_constructible<Tp, Args...>::value};

    // Is trivially default constructible
    template<typename Tp>
    struct is_trivially_default_constructible : public is_trivially_constructible<Tp>{};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto is_trivially_default_constructible_v{is_trivially_default_constructible<Tp>::value};

    // Is trivially copy constructible
    template<typename Tp>
    struct is_trivially_copy_constructible : public
            is_trivially_constructible<Tp, add_lvalue_reference_t<add_const_t<Tp>>>{};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto is_trivially_copy_constructible_v{is_trivially_copy_constructible<Tp>::value};

    // Is trivially move constructible
    template<typename Tp>
    struct is_trivially_move_constructible : public
            is_trivially_constructible<Tp, add_rvalue_reference_t<Tp>>{};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto is_trivially_move_constructible_v{is_trivially_move_constructible<Tp>::value};

    // Is trivially assignable
    template<typename Tp, typename Up>
    struct is_trivially_assignable : public bool_constant<__is_trivially_assignable(Tp, Up)>{};

    template<typename Tp, typename Up>
    [[maybe_unused]] static constexpr
    auto is_trivially_assignable_v{is_trivially_assignable<Tp, Up>::value};

    // Is trivially copy assignable
    template<typename Tp>
    struct is_trivially_copy_assignable : public
            is_trivially_assignable<add_lvalue_reference_t<Tp>,
            add_lvalue_reference_t<add_const_t<Tp>>>{};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto is_trivially_copy_assignable_v{is_trivially_copy_assignable<Tp>::value};

    // Is trivially move assignable
    template<typename Tp>
    struct is_trivially_move_assignable : public
            is_trivially_assignable<add_lvalue_reference_t<Tp>,
            add_rvalue_reference_t<Tp>>{};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto is_trivially_move_assignable_v{is_trivially_move_assignable<Tp>::value};

    // Is trivially destructible
    template<typename Tp>
    struct is_trivially_destructible : public conjunction<bool_constant<is_destructible_v<Tp>>,
            bool_constant<__has_trivial_destructor(Tp)>>{};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto is_trivially_destructible_v{is_trivially_destructible<Tp>::value};

    // Is trivially copyable
#if (__has_feature(is_trivially_copyable) || defined(_LIBCPP_COMPILER_GCC))
    template <typename Tp>
    struct is_trivially_copyable : public bool_constant<__is_trivially_copyable(Tp)> {};
#else
    template<typename Tp>
    struct is_trivially_copyable
    {
    private:
        using Up = remove_all_extents_t<remove_const_t<Tp>>;
        using has_trivial_copy_constructor = is_trivially_copy_constructible<Up>;
        using has_deleted_copy_constructor = negation<is_copy_constructible<Up>>;
        using has_trivial_move_constructor = is_trivially_move_constructible<Up>;
        using has_deleted_move_constructor = negation<is_move_constructible<Up>>;
        using has_trivial_copy_assign = is_trivially_copy_assignable<Up>;
        using has_deleted_copy_assign = negation<is_copy_assignable<Up>>;
        using has_trivial_move_assign = is_trivially_move_assignable<Up>;
        using has_deleted_move_assign = negation<is_move_assignable<Up>>;
        using has_trivial_destructor = is_trivially_destructible<Up>;
    public:
        static constexpr auto value {conjunction_v<
            has_trivial_destructor,
            disjunction<has_trivial_copy_constructor, has_deleted_copy_constructor>,
                    disjunction<has_trivial_move_constructor, has_deleted_move_constructor>,
                            disjunction<has_trivial_copy_assign, has_deleted_copy_assign>,
                                    disjunction<has_trivial_move_assign, has_deleted_move_assign>>};
    };
#endif

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_trivially_copyable_v{is_trivially_copyable<Tp>::value};

    // Is trivial
#if (__has_feature(is_trivial) || defined(_LIBCPP_COMPILER_GCC))
    template<typename Tp>
    struct is_trivial : public bool_constant<__is_trivial(Tp)> {};
#else
    template <typename Tp>
    struct is_trivial : public disjunction<is_scalar<Tp>,
            conjunction<is_trivially_copyable<Tp>, is_trivially_default_constructible<Tp>>>{};
#endif

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_trivial_v{is_trivial<Tp>::value};

    // Is standard layout
#if (__has_feature(is_standard_layout) || defined(_LIBCPP_COMPILER_GCC))
    template<typename Tp>
    struct is_standard_layout : public bool_constant<__is_standard_layout(Tp)> {};
#else
    template<typename Tp>
    struct is_standard_layout : public is_scalar<remove_all_extents_t<Tp>>{};
#endif

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_standard_layout_v{is_standard_layout<Tp>::value};

    // Is empty
#if (__has_feature(is_empty) || defined(_LIBCPP_COMPILER_GCC))
    template<typename Tp>
    struct is_empty : public bool_constant<__is_empty(Tp)> {};
#else

    namespace impl
    {
        template<typename Tp>
        struct empty_derived_class : public Tp {[[maybe_unused]] std::size_t a;};
        struct empty_base_class {[[maybe_unused]] std::size_t a;};

        template<typename Tp, bool = is_class_v<Tp>>
        struct is_empty_impl : public bool_constant<(sizeof(empty_derived_class<Tp>) == sizeof(empty_base_class) )> {};

        template<typename Tp>
        struct is_empty_impl<Tp, false> : false_type {};
    }

    template<typename Tp>
    struct is_empty : public conjunction<negation<is_union<Tp>>, impl::is_empty_impl<Tp> >{};
#endif

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_empty_v{is_empty<Tp>::value};

    // Is polymorphic

#if (__has_feature(is_polymorphic) || defined(_LIBCPP_COMPILER_GCC))
    template<typename Tp>
    struct is_polymorphic : public bool_constant<__is_polymorphic(Tp)>{};
#else
    namespace impl
    {
        template<typename Tp>
        true_type test_is_polymorphic (
                decltype(dynamic_cast<const volatile void*>(static_cast<Tp*>(nullptr)))
                );
        template<typename>
        [[maybe_unused]] false_type test_is_polymorphic(...);
    }

    template<typename Tp>
    struct is_polymorphic : conjunction<negation<is_union<Tp>>, decltype(impl::test_is_polymorphic<Tp>(nullptr))>{};
#endif

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_polymorphic_v{is_polymorphic<Tp>::value};

    // Is abstract
    template<typename Tp> struct is_abstract : public bool_constant<__is_abstract(Tp)> {};
    template<typename Tp> [[maybe_unused]] inline constexpr auto is_abstract_v{is_abstract<Tp>::value};

    // Is final
    template<typename Tp> struct is_final : public bool_constant<__is_final(Tp)> {};
    template<typename Tp> [[maybe_unused]] inline constexpr auto is_final_v{is_final<Tp>::value};

    // is aggregate
    template<typename Tp> struct is_aggregate : public bool_constant<__is_aggregate(Tp)> {};
    template<typename Tp> [[maybe_unused]] inline constexpr auto is_aggregate_v{is_aggregate<Tp>::value};

    // Is no throw constructible
    template<typename Tp, typename ... Args>
    struct is_now_throw_constructible : public bool_constant<__is_nothrow_constructible(Tp, Args...)>{};

    template<typename Tp, typename ... Args>
    [[maybe_unused]] static constexpr
    auto is_no_throw_constructible_v{is_now_throw_constructible<Tp, Args...>::value};

    // Is no throw default constructible
    template<typename Tp>
    struct is_no_throw_default_constructible :
            public bool_constant<is_no_throw_constructible_v<Tp>>{};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto is_no_throw_default_constructible_v{is_no_throw_default_constructible<Tp>::value};

    // Is no throw copy constructible
    template<typename Tp>
    struct is_no_throw_copy_constructible :
            public bool_constant<is_no_throw_constructible_v< Tp,
            add_lvalue_reference_t<add_const<Tp>>
            >>{};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto is_no_throw_copy_constructible_v{is_no_throw_copy_constructible<Tp>::value};

    // Is no throw move constructible
    template<typename Tp>
    struct is_no_throw_move_constructible :
            public bool_constant<is_no_throw_constructible_v< Tp,
                    add_rvalue_reference_t<Tp>
            >>{};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto is_no_throw_move_constructible_v{is_no_throw_move_constructible<Tp>::value};

    // Is no throw assignable
    namespace impl
    {
        template<typename Tp, typename Up>
        using is_no_throw_assignable_helper_t = decltype(noexcept(std::declval<Tp>() = std::declval<Up>()));

        template<typename , typename , typename  = void>
        struct is_no_throw_assignable_impl : public false_type {};

        template<typename Tp, typename Up>
        struct is_no_throw_assignable_impl<Tp, Up,
                void_t<is_no_throw_assignable_helper_t<Tp, Up>>> : public true_type {};
    }

    template<typename Tp, typename Up>
    struct is_no_throw_assignable : public conjunction<
            is_assignable<Tp,Up>,
            impl::is_no_throw_assignable_impl<Tp, Up>
            > {};

    template<typename Tp, typename Up>
    [[maybe_unused]] static constexpr
    auto is_no_throw_assignable_v{is_no_throw_assignable<Tp, Up>::value};

    // Is no throw copy assignable
    template<typename Tp>
    struct is_no_throw_copy_assignable : public
            is_no_throw_assignable<std::add_lvalue_reference_t<Tp>,
            add_lvalue_reference_t<add_const_t<Tp>>
            >{};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto is_no_throw_copy_assignable_v{is_no_throw_copy_assignable<Tp>::value};

    // Is no throw move assignable
    template<typename Tp>
    struct is_no_throw_move_assignable : public
            is_no_throw_assignable<std::add_lvalue_reference_t<Tp>,
            add_rvalue_reference_t<Tp>> {};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto is_no_throw_move_assignable_v{is_no_throw_move_assignable<Tp>::value};

    // Is no throw swappable with
    namespace impl
    {
        template<typename Tp, typename Up>
        using is_no_throw_swappable_with_helper_t =
                decltype(noexcept(std::swap(std::declval<Tp>(), std::declval<Up>())));

        template<typename , typename, typename = void>
        struct is_no_throw_swappable_with_impl : public false_type {};

        template<typename Tp, typename Up>
        struct is_no_throw_swappable_with_impl<Tp, Up, void_t<is_no_throw_swappable_with_helper_t<Tp, Up>,
                is_no_throw_swappable_with_helper_t<Up,Tp>>> : public true_type {};
    }

    template<typename Tp, typename Up>
    struct is_no_throw_swappable_with : public conjunction<
            impl::is_no_throw_swappable_with_impl<Tp, Up>
    > {};

    template<typename Tp, typename Up>
    [[maybe_unused]] static constexpr
    auto is_no_throw_swappable_with_v{is_no_throw_swappable_with<Tp,Up>::value};

    // Is no throw swappable
    template<typename Tp>
    struct is_no_throw_swappable : public conjunction<
            impl::is_referenceable<Tp>,
            negation<is_void<Tp>>,
            is_no_throw_swappable_with<add_lvalue_reference_t<Tp>,
                    add_lvalue_reference_t<Tp>>>{};

    template<typename Tp>
    [[maybe_unused]] static constexpr auto is_no_throw_swappable_v{is_no_throw_swappable<Tp>::value};

    // Is no throw destructible
    namespace impl
    {
        template<typename Tp>
        using is_no_throw_destructible_helper_t = decltype(noexcept(std::declval<Tp&>().~Tp()));

        template<typename , typename = void>
        struct is_no_throw_destructible_impl : public false_type {};

        template<typename Tp>
        struct is_no_throw_destructible_impl<Tp,
                void_t<is_no_throw_destructible_helper_t<Tp>>> : public true_type {};
    }

    template<typename Tp>
    struct is_no_throw_destructible : public disjunction<
            is_reference<Tp>,
            conjunction<
                    negation<is_void<Tp>>,
                    negation<is_function<Tp>>,
                    negation<is_unbounded_array<Tp>>,
                    impl::is_no_throw_destructible_impl<remove_all_extents_t<Tp>>>>{};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto is_no_throw_destructible_v{is_no_throw_destructible<Tp>::value};

    // Has virtual destructor
#if (__has_feature(has_virtual_destructor) || defined(_LIBCPP_COMPILER_GCC))
    template<typename Tp>
    struct has_virtual_destructor : public bool_constant<__has_virtual_destructor(Tp)> {};
#else
    // Only possible through compiler support. Default to false type otherwise.
    template<typename Tp>
    struct has_virtual_destructor : public false_type {};
#endif

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto has_virtual_destructor_v{has_virtual_destructor<Tp>::value};

    // Has unique object representation
    template<typename Tp>
    struct has_unique_object_representations : public bool_constant<
            __has_unique_object_representations(remove_cv_t<remove_all_extents_t<Tp>>)
            >{};

    template<typename Tp>
    [[maybe_unused]] static constexpr
    auto has_unique_object_representations_v{has_unique_object_representations<Tp>::value};

    //-------------------------------------------------------------------------------------------
    // Relationships between types
    //-------------------------------------------------------------------------------------------

    // Is base of
    template<typename Base, typename Derived>
    struct is_base_of : public bool_constant<__is_base_of(Base, Derived)>{};

    template<typename Base, typename Derived>
    [[maybe_unused]] static constexpr auto is_base_of_v{is_base_of<Base, Derived>::value};

    // Is convertible
    namespace impl
    {
        template<typename ConvertTo> static void test_convertibility(ConvertTo){};
        template<typename ConvertFrom, typename ConvertTo>
        using is_convertible_helper_t =
                decltype(test_convertibility<ConvertTo>(std::declval<ConvertFrom>()));

        template<typename, typename, typename = void>
        struct is_convertible_from_to : public false_type{};

        template<typename From, typename To>
        struct is_convertible_from_to<From,To, void_t<is_convertible_helper_t<From,To>>> :
                public true_type {};

        template<typename From, typename To,
                bool = disjunction_v<is_void<From>, is_function<To>, is_array<To>>>
        struct is_convertible_impl : public is_void<To>{};

        template<typename From, typename To>
        struct is_convertible_impl<From, To, false> : public
                is_convertible_from_to<From,To> {};
    }

    template<typename From, typename To>
    struct is_convertible : public impl::is_convertible_impl<From, To>::type {};

    template<typename From, typename To>
    [[maybe_unused]] static constexpr auto is_convertible_v{is_convertible<From, To>::value};

    // Is no throw convertible
    namespace impl
    {
        template<typename ConvertTo> static void test_no_throw_convertibility(ConvertTo) noexcept{};
        template<typename ConvertFrom, typename ConvertTo>
        using is_no_throw_convertible_helper_t = decltype(noexcept(
                test_no_throw_convertibility<ConvertTo>(std::declval<ConvertFrom>())));

        template<typename, typename, typename = void>
        struct is_no_throw_convertible_from_to : public false_type{};

        template<typename From, typename To>
        struct is_no_throw_convertible_from_to<From,To, void_t<is_no_throw_convertible_helper_t<From,To>>> :
                public true_type {};

        template<typename From, typename To,
                bool = disjunction_v<is_void<From>, is_function<To>, is_array<To>>>
        struct is_no_throw_convertible_impl : public is_void<To>{};

        template<typename From, typename To>
        struct is_no_throw_convertible_impl<From, To, false> :
                public is_no_throw_convertible_from_to<From,To> {};
    }

    template<typename From, typename To>
    struct is_no_throw_convertible : public impl::is_no_throw_convertible_impl<From, To>::type {};

    template<typename From, typename To>
    [[maybe_unused]] static constexpr auto is_no_throw_convertible_v{is_no_throw_convertible<From, To>::value};

    // Alignment of
    template<typename Tp>
    struct alignment_of : public integral_constant<std::size_t, alignof(Tp)> {};

    template<typename Tp>
    [[maybe_unused]] static constexpr auto alignment_of_v{alignment_of<Tp>::value};

    // Decay
    namespace impl
    {
        template<typename Tp>
        struct decay_impl{
        private:
            using Up = remove_reference_t<Tp>;
        public:
            using type = conditional_t<is_array_v<Tp>,
                    remove_extent_t<Tp> *,
                    conditional_t<is_function_v<Tp>,
                            add_pointer_t<Tp>,
                            remove_cv_t<Tp>>>;
        };
    }

    template<typename Tp>
    struct decay : public impl::decay_impl<Tp> {};

    template<typename Tp>
    using decay_t [[maybe_unused]] = typename decay<Tp>::type;

    // Remove cvref

    namespace impl
    {
        template<typename Tp, bool = is_reference_v<Tp> >
        struct remove_cvref_impl : public identity<remove_cv_t<remove_reference_t<Tp>>>{};

        template<typename Tp>
        struct remove_cvref_impl<Tp, false> : identity<remove_cv_t<Tp>> {};
    }

    template<typename Tp>
    struct remove_cvref : public impl::remove_cvref_impl<Tp> {};

    template<typename Tp>
    using remove_cvref_t [[maybe_unused]] = typename remove_cvref<Tp>::type;

    // Common type
    template<typename ...>
    struct common_type {};

    template<typename Tp>
    struct common_type<Tp> : public common_type<Tp, Tp> {};

    namespace impl
    {
        template<typename T1, typename T2>
        using common_type_helper = decltype(false ? std::declval<T1>() : std::declval<T2>());

        template<typename, typename, typename = void>
        struct decay_common_type {};

        template<typename T1, typename T2>
        struct decay_common_type<T1, T2, void_t<common_type_helper<T1, T2>>> : public
                decay<common_type_helper<T1, T2>>{};

        template<typename T1, typename T2, typename = void>
        struct common_type_impl : public decay_common_type<const remove_reference_t<T1>&,
                const remove_reference_t<T2> &>{};

        template<typename T1, typename T2>
        struct common_type_impl<T1, T2, void_t<common_type_helper<T1,T2>>> : public
                decay_common_type<T1, T2> {};
    }

    template<typename T1, typename T2>
    struct common_type<T1, T2> : conditional_t<
                    disjunction_v<is_not_same<T1, decay_t<T1>>, is_not_same<T2, decay_t<T2>>>,
                    common_type<decay_t<T1>,decay_t<T2>>,
                    impl::common_type_impl<T1,T2>> {};

    namespace impl
    {
        template<typename VoidType, typename, typename, typename ...>
        struct common_type_sequence_impl {};

        template<typename T1, typename T2, typename ... Sequence>
        struct common_type_sequence_impl<void_t<typename common_type<T1, T2>::type>, T1, T2, Sequence...> :
                common_type<typename common_type<T1, T2>::type, Sequence...> {};
    }

    template<typename T1, typename T2, typename ... Sequence>
    struct common_type<T1, T2, Sequence...> : public impl::common_type_sequence_impl<void, T1, T2, Sequence...> {};

    template<typename ... Sequence>
    using common_type_t [[maybe_unused]] = typename common_type<Sequence...>::type;

    // Underlying type
    namespace impl
    {
        template<typename Tp, bool = is_enum_v<Tp>> struct underlying_type_impl {};

        template<typename Tp>
        struct underlying_type_impl<Tp, true> : public identity<__underlying_type(Tp)> {};
    }

    template<typename Tp>
    struct underlying_type : public impl::underlying_type_impl<Tp> {};

    template<typename Tp>
    using underlying_type_t [[maybe_unused]] = typename underlying_type<Tp>::type;


}
