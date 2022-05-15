//
// Created by chazz on 09/05/22.
//

#pragma once


#include "arithmetic.hpp"

namespace bazaar::traits {

    using nullptr_t = decltype(nullptr);
    template<typename ...> using void_t = void;

    // Identity
    template<typename Tp>
    struct identity {using type = Tp;};

    //------------------------------------- Helper traits ---------------------------------------

    // Enable_if
    template<bool, class Tp = void>
    struct enable_if : public identity<Tp> {};

    template<class Tp>
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
    struct conditional_to_type : public impl::conditional_impl<Condition, true_type , false_type>{};

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
    using is_same = impl::is_same_impl<Tp,Up>;

    template<typename Tp, typename Up>
    using is_not_same = not_bool_constant_t<typename impl::is_same_impl<Tp,Up>::type>;

    template<typename Tp, typename Up>
    inline constexpr bool is_same_v = is_same<Tp, Up>::value;

    template<typename Tp, typename Up>
    inline constexpr bool is_not_same_v = is_not_same<Tp, Up>::value;

    // Is one of
    namespace impl
    {
        template<typename Tp, typename ... Sequence> struct is_one_of_impl;
        template<typename Tp> struct is_one_of_impl <Tp> : public false_type {};
        template<typename Tp, typename ... Sequence> struct is_one_of_impl<Tp, Tp, Sequence...> :  public true_type {};
        template<typename Tp, typename Up, typename ... Sequence>
        struct is_one_of_impl<Tp, Up, Sequence...> : public is_one_of_impl<Tp, Sequence...>{};
    }

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

    //-------------------- Const-volatile properties and transformations ------------------------

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

    //------------------------------ Primary classification traits ------------------------------

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
    [[maybe_unused]] inline constexpr bool is_null_pointer_v = impl::is_null_pointer_impl<Tp>::value;

    // Is integral and floating
    template<typename Tp>
    struct is_integral : public impl::is_integral_impl<remove_cv_t<Tp>> {};
    template<typename Tp>
    [[maybe_unused]] inline constexpr bool is_integral_v = is_integral<Tp>::value;

    template<typename Tp>
    struct is_floating_point : public impl::is_floating_point_impl<remove_cv_t<Tp>> {};
    template<typename Tp>
    [[maybe_unused]] inline constexpr bool is_floating_v = is_floating_point<Tp>::value;

    template<typename Tp>
    struct is_signed_integer : public impl::is_signed_integer_impl<remove_cv_t<Tp>>{};
    template<typename Tp>
    [[maybe_unused]] inline constexpr bool is_signed_integer_v = is_signed_integer<Tp>::value;

    template<typename Tp>
    struct is_unsigned_integer : public impl::is_unsigned_integer_impl<remove_cv_t<Tp>>{};
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
    template<typename Tp> struct is_reference : public false_type {};
    template<typename Tp> struct is_reference<Tp&> : public true_type {};
    template<typename Tp> struct is_reference<Tp&&> : public true_type {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_reference_v = is_reference<Tp>::value;

    // Is function
    template<typename Tp>
    struct is_function : public conditional_to_type<
            !(std::is_const_v<const Tp> || std::is_reference_v<Tp>)>{};

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
    struct is_member_object_pointer : public conditional_to_type<
            is_member_pointer_v<Tp> && !is_function_v<Tp>
            >{};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_member_object_pointer_v {is_member_object_pointer<Tp>::value};

    // Is member function pointer
    template<typename Tp>
    struct is_member_function_pointer : public conditional_to_type<
            is_member_pointer_v<Tp> && is_function_v<Tp>>{};

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
    inline constexpr auto is_union_v{is_union<Tp>::value};

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
    template<typename Tp> struct is_enum : public bool_constant<
                                !is_void_v<Tp>              &&
                                !is_arithmetic_v<Tp>        &&
                                !is_array_v<Tp>             &&
                                !is_pointer_v<Tp>           &&
                                !is_reference_v<Tp>         &&
                                !is_member_pointer_v<Tp>    &&
                                !is_union_v<Tp>             &&
                                !is_class_v<Tp>             &&
                                !is_function_v<Tp>>{};
#endif

    template<typename Tp>
    inline constexpr auto is_enum_v{is_enum<Tp>::value};

    //----------------------------- Secondary classification traits -----------------------------



    //-------------------------------- Reference transformations --------------------------------

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
                : public conditional_to_type<is_not_same_v<is_non_referenceable_type,
                        decltype(test_is_referenceable<Tp>(0))>> {
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

    // Remove pointer
    namespace impl
    {
        template<typename Tp>
        struct remove_pointer_helper : public identity<Tp>{};

        template<typename Tp>
        struct remove_pointer_helper<Tp*> : public identity<Tp>{};

        template<typename Tp, bool = is_pointer_v<Tp>>
        struct remove_pointer_impl : public identity<Tp> {};

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

    // Is signed

    namespace impl
    {
        template<typename Tp, bool = is_integral_v<Tp>>
        struct is_signed_impl  : public conditional_to_type<Tp(-1) < Tp(0)>{};

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
        struct is_unsigned_impl  : public conditional_to_type<Tp(0) < Tp(-1)>{};

        template<typename Tp> // floating point is signed by default
        struct is_unsigned_impl<Tp, false> : public false_type {};
    }

    template<typename Tp, bool = is_arithmetic_v<Tp>>
    struct is_unsigned : public impl::is_unsigned_impl<Tp>{};

    template<typename Tp>
    struct is_unsigned<Tp, false> : public false_type {};

    template<typename Tp>
    [[maybe_unused]] inline constexpr auto is_unsigned_v {is_unsigned<Tp>::value};
}
