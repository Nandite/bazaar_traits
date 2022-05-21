//
// Created by chazz on 14/05/22.
//

#ifndef BAZAAR_SYNOPSIS_HPP
#define BAZAAR_SYNOPSIS_HPP
/*
namespace bazaar
{
    //-------------------------------------------------------------------------------------------
    // helper_traits.hpp
    //-------------------------------------------------------------------------------------------
    using nullptr_t;
    template<typename Tp> struct identity;
    template <bool, typename Tp = void> struct enable_if;
    template<bool Condition, typename If, typename Else> struct conditional
    template<typename Tp, typename Up> struct is_same;
    template<typename Tp, typename ... Sequence> struct is_one_of;

    //-------------------------------------------------------------------------------------------
    // integral_constant.hpp
    //-------------------------------------------------------------------------------------------
    template<typename Tp, Tp v> struct integral_constant;
    template<bool v> using bool_constant;
    using true_type = bool_constant<true>;
    using false_type = bool_constant<false>;
    template<typename Tp> struct invert_bool_constant;

    //-------------------------------------------------------------------------------------------
    // arithmetic.hpp
    //-------------------------------------------------------------------------------------------
    template<std::size_t ... Sequence> struct static_max;
    template<std::size_t ... Sequence> struct static_min;

    //-------------------------------------------------------------------------------------------
    // logical_operators.hpp
    //-------------------------------------------------------------------------------------------
    template<typename ... Bn> struct conjunction;
    template<typename ... Bn> struct disjunction;
    template<typename B> struct negation;

    //-------------------------------------------------------------------------------------------
    // bazaar_traits.hpp
    //-------------------------------------------------------------------------------------------

    // Reference transformations:
    template<typename Tp> struct remove_reference;
    template<typename Tp> struct add_lvalue_reference;
    template<typename Tp> struct add_rvalue_reference;

    // Const-volatile properties and transformations:
    template<typename Tp> struct is_const;
    template<typename Tp> struct is_volatile;
    template <typename Tp> struct remove_const;
    template <typename Tp> struct remove_volatile;
    template<typename Tp> struct remove_cv;
    template<typename Tp> struct add_const;
    template<typename Tp> struct add_volatile;
    template<typename Tp> struct add_cv;
    template<typename In, typename Out> struct apply_cv;

    // Primary classification traits:
    template<typename Tp> struct is_void;
    template<typename Tp> struct is_null_pointer;
    template<typename Tp> struct is_integral;
    template<typename Tp> struct is_floating_point;
    template<typename Tp> struct is_signed_integer;
    template<typename Tp> struct is_unsigned_integer;
    template<typename T> struct is_arithmetic;
    template<typename Tp> struct is_array;
    template<typename Tp> struct is_pointer;
    template<typename Tp> struct is_lvalue_reference;
    template<typename Tp> struct is_rvalue_reference;
    template<typename Tp> struct is_reference;
    template<typename Tp> struct is_function;
    template<typename Tp> struct is_member_pointer;
    template<typename Tp> struct is_member_object_pointer;
    template<typename Tp> struct is_member_function_pointer;
    template<typename Tp> struct is_union;
    template<typename Tp> struct is_class;
    template<typename Tp> struct is_enum;

    // Secondary classification traits:
    template<typename Tp> struct is_fundamental;
    template<typename Tp> struct is_scalar;
    template<typename Tp> struct is_object;
    template<typename Tp> struct is_compound;

    // Pointer transformations:
    template<typename Tp> struct remove_pointer;
    template<typename Tp> struct add_pointer;

    // Integral properties:
    template<typename Tp> struct is_signed;
    template<typename Tp> struct is_unsigned;
    template<typename Tp> struct make_signed;
    template<typename Tp> struct make_unsigned;

    // Array properties and transformations:
    template<typename Tp> struct rank;
    template<typename Tp, std::size_t N = 0> struct extent;
    template<typename Tp> struct remove_extent;
    template<typename Tp> struct remove_all_extents;
    template<typename Tp> struct is_bounded_array;
    template<typename Tp> struct is_unbounded_array;

    // Member introspection:
    template <class T, class... Args> struct is_constructible;
    template <class T>                struct is_default_constructible;
    template <class T>                struct is_copy_constructible;
    template <class T>                struct is_move_constructible;
    template <class T, class U>       struct is_assignable;
    template <class T>                struct is_copy_assignable;
    template <class T>                struct is_move_assignable;
    template <class T, class U>       struct is_swappable_with;       // C++17
    template <class T>                struct is_swappable;            // C++17
    template <class T>                struct is_destructible;

    template <class T, class... Args> struct is_trivially_constructible;
    template <class T>                struct is_trivially_default_constructible;
    template <class T>                struct is_trivially_copy_constructible;
    template <class T>                struct is_trivially_move_constructible;
    template <class T, class U>       struct is_trivially_assignable;
    template <class T>                struct is_trivially_copy_assignable;
    template <class T>                struct is_trivially_move_assignable;
    template <class T>                struct is_trivially_destructible;

    template <class T> struct is_trivially_copyable;
    template <class T> struct is_trivial;
    template <class T> struct is_standard_layout;
    template <class T> struct is_empty;
    template <class T> struct is_polymorphic;
    template <class T> struct is_abstract;
    template <class T> struct is_final; // C++14
    template <class T> struct is_aggregate; // C++17

    template <class T, class... Args> struct is_nothrow_constructible;
    template <class T>                struct is_nothrow_default_constructible;
    template <class T>                struct is_nothrow_copy_constructible;
    template <class T>                struct is_nothrow_move_constructible;
    template <class T, class U>       struct is_nothrow_assignable;
    template <class T>                struct is_nothrow_copy_assignable;
    template <class T>                struct is_nothrow_move_assignable;
    template <class T, class U>       struct is_nothrow_swappable_with; // C++17
    template <class T>                struct is_nothrow_swappable;      // C++17
    template <class T>                struct is_nothrow_destructible;

    template <class T> struct has_virtual_destructor;

    template<class T> struct has_unique_object_representations;         // C++17

    // Relationships between types:
    template <class Base, class Derived> struct is_base_of;
    template <class From, class To> struct is_convertible;
    template <typename From, typename To> struct is_nothrow_convertible;                  // C++20
    template <typename From, typename To> inline constexpr bool is_nothrow_convertible_v; // C++20

    // Alignment properties and transformations:
    template<typename Tp> struct alignment_of;
    template<typename Tp> struct decay;
    template<typename Tp> struct remove_cvref;
    template<typename ...> struct common_type
    template<typename Tp> struct underlying_type;

    // Todo : implement theses
    template <class Fn, class... ArgTypes> struct is_invocable;
    template <class R, class Fn, class... ArgTypes> struct is_invocable_r;
    template <class Fn, class... ArgTypes> struct is_nothrow_invocable;
    template <class R, class Fn, class... ArgTypes> struct is_nothrow_invocable_r;
    template <class Fn, class... ArgTypes> struct invoke_result;  // C++17
    template <size_t Len, size_t Align = most_stringent_alignment_requirement> struct aligned_storage;
    template <size_t Len, class... Types> struct aligned_union;

}*/

#endif //BAZAAR_SYNOPSIS_HPP
