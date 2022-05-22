#include <utility>
#include <array>
#include "include/bazaar_traits.hpp"
#include "include/arithmetic.hpp"

struct Tp {};
namespace bzt = bazaar::traits;

[[maybe_unused]] void test_rank() {
    static_assert(std::rank_v<int> == bzt::rank_v<int>);
    static_assert(std::rank_v<int[5]> == bzt::rank_v<int[5]>);
    static_assert(std::rank_v<int[5][5]> == bzt::rank_v<int[5][5]>);
    static_assert(std::rank_v<int[][5][5]> == bzt::rank_v<int[][5][5]>);

    [[maybe_unused]] int ary[][3]={};
    static_assert(std::rank_v<decltype(ary[0])> == bzt::rank_v<decltype(ary[0])>);
    static_assert(std::is_same_v<decltype(ary[0]), int(&)[3]>);
    static_assert(std::rank_v<std::remove_cvref_t<decltype(ary[0])>>
            == bzt::rank_v<bzt::remove_cvref_t<decltype(ary[0])>>);
}

[[maybe_unused]] void test_extent() {
    static_assert(std::extent_v<int[3]> == bzt::extent_v<int[3]>);
    static_assert(std::extent_v<int[3][4], 0> == bzt::extent_v<int[3][4], 0>);
    static_assert(std::extent_v<int[3][4], 1> == bzt::extent_v<int[3][4], 1>);
    static_assert(std::extent_v<int[3][4], 2> == bzt::extent_v<int[3][4], 2>);
    static_assert(std::extent_v<int[]> == bzt::extent_v<int[]>);

    const int ints[] = {1,2,3,4};
    static_assert(std::extent_v<decltype(ints)> == bzt::extent_v<decltype(ints)>);

    [[maybe_unused]] int ary[][3]={};
    static_assert(std::extent_v<decltype(ary[0])> == bzt::extent_v<decltype(ary[0])>);
    static_assert(std::extent_v<std::remove_cvref_t<decltype(ary[0])>>
                == bzt::extent_v<bzt::remove_cvref_t<decltype(ary[0])>>);
}

[[maybe_unused]] void test_remove_extent() {
    static_assert(std::is_same_v<std::remove_extent_t<int>, bzt::remove_extent_t<int>>);
    static_assert(std::is_same_v<std::remove_extent_t<int[2]>, bzt::remove_extent_t<int[2]>>);
    static_assert(std::is_same_v<std::remove_extent_t<Tp>, bzt::remove_extent_t<Tp>>);
    static_assert(std::is_same_v<std::remove_extent_t<Tp[2][4]>, bzt::remove_extent_t<Tp[2][4]>>);
    static_assert(std::is_same_v<std::remove_extent_t<int[]>, bzt::remove_extent_t<int[]>>);
    static_assert(std::is_same_v<std::remove_extent_t<int[2][10]>, bzt::remove_extent_t<int[2][10]>>);
    static_assert(std::is_same_v<std::remove_extent_t<int[][6]>, bzt::remove_extent_t<int[][6]>>);
}

[[maybe_unused]] void test_all_remove_extents() {
    static_assert(std::is_same_v<std::remove_all_extents_t<float>, bzt::remove_all_extents_t<float>>);
    static_assert(std::is_same_v<std::remove_all_extents_t<float[1][2][3]>, bzt::remove_all_extents_t<float[1][2][3]>>);
    static_assert(std::is_same_v<std::remove_all_extents_t<float [1][1][1][1][2]>,
            bzt::remove_all_extents_t<float [1][1][1][1][2]>>);
    static_assert(std::is_same_v<std::remove_all_extents_t<float*>, bzt::remove_all_extents_t<float*>>);
    static_assert(std::is_same_v<std::remove_all_extents_t<int[3][2]>, bzt::remove_all_extents_t<int[3][2]>>);
    static_assert(std::is_same_v<std::remove_all_extents_t<double[2][3]>, bzt::remove_all_extents_t<double[2][3]>>);
    struct X { int m; };
    static_assert(std::is_same_v<std::remove_all_extents_t<X[3][3]>, bzt::remove_all_extents_t<X[3][3]>>);
}

[[maybe_unused]] void test_is_bounded_array() {
    static_assert(std::is_bounded_array_v<Tp> == bzt::is_bounded_array_v<Tp>);
    static_assert(std::is_bounded_array_v<Tp[]> == bzt::is_bounded_array_v<Tp[]>);
    static_assert(std::is_bounded_array_v<Tp[3]> == bzt::is_bounded_array_v<Tp[3]>);
    static_assert(std::is_bounded_array_v<float> == bzt::is_bounded_array_v<float>);
    static_assert(std::is_bounded_array_v<int> == bzt::is_bounded_array_v<int>);
    static_assert(std::is_bounded_array_v<int[]> == bzt::is_bounded_array_v<int[]>);
    static_assert(std::is_bounded_array_v<int[3]> == bzt::is_bounded_array_v<int[3]>);
}

[[maybe_unused]] void test_is_unbounded_array() {
    static_assert(std::is_unbounded_array_v<Tp> == bzt::is_unbounded_array_v<Tp>);
    static_assert(std::is_unbounded_array_v<Tp[]> == bzt::is_unbounded_array_v<Tp[]>);
    static_assert(std::is_unbounded_array_v<Tp[3]> == bzt::is_unbounded_array_v<Tp[3]>);
    static_assert(std::is_unbounded_array_v<float> == bzt::is_unbounded_array_v<float>);
    static_assert(std::is_unbounded_array_v<int> == bzt::is_unbounded_array_v<int>);
    static_assert(std::is_unbounded_array_v<int[]> == bzt::is_unbounded_array_v<int[]>);
    static_assert(std::is_unbounded_array_v<int[3]> == bzt::is_unbounded_array_v<int[3]>);
}

[[maybe_unused]] void test_remove_reference() {
    static_assert(std::is_same_v<int, bzt::remove_reference_t<int>>);
    static_assert(std::is_same_v<int, bzt::remove_reference_t<int&>>);
    static_assert(std::is_same_v<int, bzt::remove_reference_t<int&&>>);

    static_assert(std::is_same_v<const int, bzt::remove_reference_t<const int>>);
    static_assert(std::is_same_v<const int, bzt::remove_reference_t<const int&>>);
    static_assert(std::is_same_v<const int, bzt::remove_reference_t<const int&&>>);

    static_assert(std::is_same_v<volatile int, bzt::remove_reference_t<volatile int>>);
    static_assert(std::is_same_v<volatile int, bzt::remove_reference_t<volatile int&>>);
    static_assert(std::is_same_v<volatile int, bzt::remove_reference_t<volatile int&&>>);

    static_assert(std::is_same_v<const volatile int, bzt::remove_reference_t<const volatile int>>);
    static_assert(std::is_same_v<const volatile int, bzt::remove_reference_t<const volatile int&>>);
    static_assert(std::is_same_v<const volatile int, bzt::remove_reference_t<const volatile int&&>>);

    static_assert(std::is_same_v<int*, bzt::remove_reference_t<int*>>);
    static_assert(std::is_same_v<int**, bzt::remove_reference_t<int**>>);
    static_assert(std::is_same_v<int[], bzt::remove_reference_t<int[]>>);
}

[[maybe_unused]] void test_add_lvalue_or_rvalue_reference() {
    using nonref = int;
    using lref = typename bzt::add_lvalue_reference<nonref>::type;
    using rref = typename bzt::add_rvalue_reference<nonref>::type;
    using voidref = std::add_lvalue_reference_t<void>;
    static_assert(!std::is_lvalue_reference<nonref>::value);
    static_assert(!std::is_rvalue_reference<nonref>::value);
    static_assert(std::is_lvalue_reference<lref>::value);
    static_assert(std::is_rvalue_reference<rref>::value);
    static_assert(!std::is_rvalue_reference<lref>::value);
    static_assert(!std::is_lvalue_reference<rref>::value);
    static_assert(!std::is_lvalue_reference<voidref>::value);
    static_assert(!std::is_rvalue_reference<voidref>::value);
}

[[maybe_unused]] void test_is_const() {
    static_assert(!bzt::is_const_v<int>);
    static_assert(bzt::is_const_v<const int>);
    static_assert(!bzt::is_const_v<const int* >);
    static_assert(bzt::is_const_v<int * const>);
    static_assert(!bzt::is_const_v<const int&>);
    static_assert(bzt::is_const_v<bzt::remove_reference_t<const int&>>);
}

[[maybe_unused]] void test_is_volatile() {
    static_assert(!bzt::is_volatile_v<int>);
    static_assert(bzt::is_volatile_v<volatile int>);
    static_assert(bzt::is_volatile_v<int * volatile>);
    static_assert(bzt::is_volatile_v<int ** volatile>);
    static_assert(bzt::is_volatile_v<volatile int[]>);
    static_assert(!bzt::is_volatile_v<volatile int&>);
}

[[maybe_unused]] void test_remove_const_volatile_and_cv() {
    static_assert(std::is_same_v<bzt::remove_cv_t<int>, int>);
    static_assert(std::is_same_v<bzt::remove_cv_t<volatile int >, int >);
    static_assert(std::is_same_v<bzt::remove_cv_t<const volatile int >, int>);
    static_assert(std::is_same_v<bzt::remove_cv_t<const volatile int* >, const volatile int* >);
    static_assert(std::is_same_v<bzt::remove_cv_t<const int* volatile >, const int* >);
    static_assert(std::is_same_v<bzt::remove_cv_t< int* const volatile >, int* >);

    using type1 = bzt::remove_cv<const int>::type;
    using type2 = bzt::remove_cv<volatile int>::type;
    using type3 = bzt::remove_cv<const volatile int>::type;
    using type4 = bzt::remove_cv<const volatile int*>::type;
    using type5 = bzt::remove_cv<int* const volatile>::type;

    static_assert(std::is_same_v<type1, int>);
    static_assert(std::is_same_v<type2, int>);
    static_assert(std::is_same_v<type3, int>);
    static_assert(!std::is_same_v<type4, int*>);
    static_assert(std::is_same_v<type4, const volatile int*>);
    static_assert(std::is_same_v<type5, int*>);
}

[[maybe_unused]] void test_add_const_volatile_and_cv() {
    static_assert(std::is_same_v<bzt::add_const_t<int>, const int>);
    static_assert(std::is_same_v<bzt::add_const_t<const int>, const int>);
    static_assert(std::is_same_v<bzt::add_const_t<Tp>, const Tp>);
    static_assert(std::is_same_v<bzt::add_const_t<int *>, int * const>);
    static_assert(std::is_same_v<bzt::add_const_t<int[]>, const int[]>);
    static_assert(std::is_same_v<bzt::add_const_t<int&>, int &>);
    static_assert(std::is_same_v<bzt::add_const_t<int**>, int** const>);

    static_assert(std::is_same_v<bzt::add_volatile_t<int>, volatile int>);
    static_assert(std::is_same_v<bzt::add_volatile_t<volatile int>, volatile  int>);
    static_assert(std::is_same_v<bzt::add_volatile_t<Tp>, volatile Tp>);
    static_assert(std::is_same_v<bzt::add_volatile_t<int *>, int * volatile>);
    static_assert(std::is_same_v<bzt::add_volatile_t<int[]>, volatile int[]>);
    static_assert(std::is_same_v<bzt::add_volatile_t<int&>, int &>);
    static_assert(std::is_same_v<bzt::add_volatile_t<int**>, int** volatile>);

    static_assert(std::is_same_v<bzt::add_cv_t<int>, const volatile int>);
    static_assert(std::is_same_v<bzt::add_cv_t<Tp>, const volatile Tp>);
    static_assert(std::is_same_v<bzt::add_cv_t<int *>, int * const volatile>);
    static_assert(std::is_same_v<bzt::add_cv_t<int[]>, const volatile int[]>);
    static_assert(std::is_same_v<bzt::add_cv_t<int&>, int &>);
    static_assert(std::is_same_v<bzt::add_cv_t<int**>, int** const volatile>);
    static_assert(std::is_same_v<bzt::add_cv_t<int**>, int** volatile const >);
}

[[maybe_unused]] void test_is_void() {
    static_assert(bzt::is_void_v<void>);
    static_assert(bzt::is_void_v<void const>);
    static_assert(bzt::is_void_v<void volatile>);
    static_assert(bzt::is_void_v<void const volatile>);
    static_assert(!bzt::is_void_v<int>);
    static_assert(!bzt::is_void_v<void*>);
    static_assert(!bzt::is_void_v<Tp[]>);
    static_assert(!bzt::is_void_v<Tp[5]>);
}

[[maybe_unused]] void test_is_null_pointer() {
    static_assert(bzt::is_null_pointer_v<decltype(nullptr)>);
    static_assert(bzt::is_null_pointer_v<std::nullptr_t>);
    static_assert(!bzt::is_null_pointer_v<int*>);
    static_assert(bzt::is_null_pointer_v<const decltype(nullptr)>);
    static_assert(bzt::is_null_pointer_v<volatile decltype(nullptr)>);
    static_assert(bzt::is_null_pointer_v<const volatile decltype(nullptr)>);
    static_assert(!bzt::is_null_pointer_v<Tp[5]>);
    static_assert(!bzt::is_null_pointer_v<Tp[]>);
    static_assert(!bzt::is_null_pointer_v<Tp**>);
    static_assert(!bzt::is_null_pointer_v<std::nullptr_t *>);
}

[[maybe_unused]] void test_is_integral() {
    enum E : int {};
    static_assert(!bzt::is_integral_v<Tp>);
    static_assert(!bzt::is_integral_v<E>);
    static_assert(bzt::is_integral_v<std::underlying_type_t<E>>);
    static_assert(!bzt::is_integral_v<float>);
    static_assert(!bzt::is_integral_v<double>);
    static_assert(!bzt::is_integral_v<long double>);
    static_assert(bzt::is_integral_v<int>);
    static_assert(bzt::is_integral_v<const int>);
    static_assert(bzt::is_integral_v<volatile int>);
    static_assert(bzt::is_integral_v<const volatile int>);
    static_assert(bzt::is_integral_v<unsigned char>);
    static_assert(bzt::is_integral_v<signed char>);
    static_assert(!bzt::is_integral_v<const int *>);
    static_assert(!bzt::is_integral_v<int**>);
    static_assert(!bzt::is_integral_v<int[]>);
    static_assert(!bzt::is_integral_v<int[5]>);
    static_assert(bzt::is_integral_v<bool>);
    static_assert(bzt::is_integral_v<const bool>);
    static_assert(!bzt::is_integral_v<const int&>);
}

[[maybe_unused]] void test_is_floating_point() {
    enum E : int {};
    static_assert(!bzt::is_floating_v<Tp>);
    static_assert(!bzt::is_floating_v<E>);
    static_assert(!bzt::is_floating_v<std::underlying_type_t<E>>);
    static_assert(bzt::is_floating_v<float>);
    static_assert(bzt::is_floating_v<double>);
    static_assert(bzt::is_floating_v<long double>);
    static_assert(bzt::is_floating_v<const float>);
    static_assert(bzt::is_floating_v<const double>);
    static_assert(bzt::is_floating_v<const long double>);
    static_assert(bzt::is_floating_v<volatile float>);
    static_assert(bzt::is_floating_v<volatile double>);
    static_assert(bzt::is_floating_v<volatile long double>);
    static_assert(bzt::is_floating_v<const volatile float>);
    static_assert(bzt::is_floating_v<const volatile double>);
    static_assert(bzt::is_floating_v<const volatile long double>);
    static_assert(!bzt::is_floating_v<float*>);
    static_assert(!bzt::is_floating_v<double*>);
    static_assert(!bzt::is_floating_v<long double*>);
    static_assert(!bzt::is_floating_v<float[]>);
    static_assert(!bzt::is_floating_v<double[]>);
    static_assert(!bzt::is_floating_v<long double[]>);
    static_assert(!bzt::is_floating_v<float[5]>);
    static_assert(!bzt::is_floating_v<double[5]>);
    static_assert(!bzt::is_floating_v<long double[5]>);
}

[[maybe_unused]] void test_is_signed_integer() {
    static_assert(bzt::is_signed_integer_v<signed char>);
    static_assert(bzt::is_signed_integer_v<signed short>);
    static_assert(bzt::is_signed_integer_v<signed int>);
    static_assert(bzt::is_signed_integer_v<signed long>);
    static_assert(bzt::is_signed_integer_v<signed long long>);
    static_assert(bzt::is_signed_integer_v<const signed char>);
    static_assert(bzt::is_signed_integer_v<const signed short>);
    static_assert(bzt::is_signed_integer_v<const signed int>);
    static_assert(bzt::is_signed_integer_v<const signed long>);
    static_assert(bzt::is_signed_integer_v<const signed long long>);
    static_assert(bzt::is_signed_integer_v<signed long long>);
    static_assert(bzt::is_signed_integer_v<volatile signed char>);
    static_assert(bzt::is_signed_integer_v<volatile signed short>);
    static_assert(bzt::is_signed_integer_v<volatile signed int>);
    static_assert(bzt::is_signed_integer_v<volatile signed long>);
    static_assert(bzt::is_signed_integer_v<volatile signed long long>);
    static_assert(bzt::is_signed_integer_v<const volatile signed char>);
    static_assert(bzt::is_signed_integer_v<const volatile signed short>);
    static_assert(bzt::is_signed_integer_v<const volatile signed int>);
    static_assert(bzt::is_signed_integer_v<const volatile signed long>);
    static_assert(bzt::is_signed_integer_v<const volatile signed long long>);
    static_assert(!bzt::is_signed_integer_v<unsigned char>);
    static_assert(!bzt::is_signed_integer_v<unsigned short>);
    static_assert(!bzt::is_signed_integer_v<unsigned int>);
    static_assert(!bzt::is_signed_integer_v<unsigned long>);
    static_assert(!bzt::is_signed_integer_v<unsigned long long>);
    static_assert(!bzt::is_signed_integer_v<volatile float>);
    static_assert(!bzt::is_signed_integer_v<volatile double>);
    static_assert(!bzt::is_signed_integer_v<volatile long double>);
    static_assert(!bzt::is_signed_integer_v<const volatile float>);
    static_assert(!bzt::is_signed_integer_v<const volatile double>);
    static_assert(!bzt::is_signed_integer_v<const volatile long double>);
    static_assert(!bzt::is_signed_integer_v<float*>);
    static_assert(!bzt::is_signed_integer_v<double*>);
    static_assert(!bzt::is_signed_integer_v<long double*>);
    static_assert(!bzt::is_signed_integer_v<float[]>);
    static_assert(!bzt::is_signed_integer_v<double[]>);
    static_assert(!bzt::is_signed_integer_v<long double[]>);
    static_assert(!bzt::is_signed_integer_v<float[5]>);
    static_assert(!bzt::is_signed_integer_v<double[5]>);
    static_assert(!bzt::is_signed_integer_v<long double[5]>);
}

[[maybe_unused]] void test_is_unsigned_integer() {
    static_assert(bzt::is_unsigned_integer_v<unsigned char>);
    static_assert(bzt::is_unsigned_integer_v<unsigned short>);
    static_assert(bzt::is_unsigned_integer_v<unsigned int>);
    static_assert(bzt::is_unsigned_integer_v<unsigned long>);
    static_assert(bzt::is_unsigned_integer_v<unsigned long long>);
    static_assert(bzt::is_unsigned_integer_v<const unsigned char>);
    static_assert(bzt::is_unsigned_integer_v<const unsigned short>);
    static_assert(bzt::is_unsigned_integer_v<const unsigned int>);
    static_assert(bzt::is_unsigned_integer_v<const unsigned long>);
    static_assert(bzt::is_unsigned_integer_v<const unsigned long long>);
    static_assert(bzt::is_unsigned_integer_v<unsigned long long>);
    static_assert(bzt::is_unsigned_integer_v<volatile unsigned char>);
    static_assert(bzt::is_unsigned_integer_v<volatile unsigned short>);
    static_assert(bzt::is_unsigned_integer_v<volatile unsigned int>);
    static_assert(bzt::is_unsigned_integer_v<volatile unsigned long>);
    static_assert(bzt::is_unsigned_integer_v<volatile unsigned long long>);
    static_assert(bzt::is_unsigned_integer_v<const volatile unsigned char>);
    static_assert(bzt::is_unsigned_integer_v<const volatile unsigned short>);
    static_assert(bzt::is_unsigned_integer_v<const volatile unsigned int>);
    static_assert(bzt::is_unsigned_integer_v<const volatile unsigned long>);
    static_assert(bzt::is_unsigned_integer_v<const volatile unsigned long long>);
    static_assert(!bzt::is_unsigned_integer_v<signed char>);
    static_assert(!bzt::is_unsigned_integer_v<signed short>);
    static_assert(!bzt::is_unsigned_integer_v<signed int>);
    static_assert(!bzt::is_unsigned_integer_v<signed long>);
    static_assert(!bzt::is_unsigned_integer_v<signed long long>);
    static_assert(!bzt::is_unsigned_integer_v<volatile float>);
    static_assert(!bzt::is_unsigned_integer_v<volatile double>);
    static_assert(!bzt::is_unsigned_integer_v<volatile long double>);
    static_assert(!bzt::is_unsigned_integer_v<const volatile float>);
    static_assert(!bzt::is_unsigned_integer_v<const volatile double>);
    static_assert(!bzt::is_unsigned_integer_v<const volatile long double>);
    static_assert(!bzt::is_unsigned_integer_v<float*>);
    static_assert(!bzt::is_unsigned_integer_v<double*>);
    static_assert(!bzt::is_unsigned_integer_v<long double*>);
    static_assert(!bzt::is_unsigned_integer_v<float[]>);
    static_assert(!bzt::is_unsigned_integer_v<double[]>);
    static_assert(!bzt::is_unsigned_integer_v<long double[]>);
    static_assert(!bzt::is_unsigned_integer_v<float[5]>);
    static_assert(!bzt::is_unsigned_integer_v<double[5]>);
    static_assert(!bzt::is_unsigned_integer_v<long double[5]>);
}

[[maybe_unused]] void test_is_arithmetic() {
    static_assert(!bzt::is_arithmetic_v<Tp>);
    static_assert(bzt::is_arithmetic_v<bool>);
    static_assert(bzt::is_arithmetic_v<int>);
    static_assert(bzt::is_arithmetic_v<int const>);
    static_assert(bzt::is_arithmetic_v<int volatile>);
    static_assert(bzt::is_arithmetic_v<int const volatile>);
    static_assert(!bzt::is_arithmetic_v<int&>);
    static_assert(!bzt::is_arithmetic_v<int*>);
    static_assert(bzt::is_arithmetic_v<float>);
    static_assert(bzt::is_arithmetic_v<float const>);
    static_assert(bzt::is_arithmetic_v<float volatile>);
    static_assert(bzt::is_arithmetic_v<float const volatile>);
    static_assert(!bzt::is_arithmetic_v<float&>);
    static_assert(!bzt::is_arithmetic_v<float*>);
    static_assert(bzt::is_arithmetic_v<char>);
    static_assert(bzt::is_arithmetic_v<char const>);
    static_assert(!bzt::is_arithmetic_v<char&>);
    static_assert(!bzt::is_arithmetic_v<char*>);
}

[[maybe_unused]] void test_is_array() {
    static_assert(!bzt::is_array_v<Tp>);
    static_assert(bzt::is_array_v<Tp[]>);
    static_assert(bzt::is_array_v<Tp[5]>);
    static_assert(!bzt::is_array_v<float>);
    static_assert(!bzt::is_array_v<int>);
    static_assert(bzt::is_array_v<int[]>);
    static_assert(bzt::is_array_v<int[5]>);
    static_assert(bzt::is_array_v<const int[]>);
    static_assert(bzt::is_array_v<volatile int[5]>);
    static_assert(bzt::is_array_v<const volatile int[]>);
    static_assert(bzt::is_array_v<float[6]>);
    static_assert(bzt::is_array_v<float[]>);
    static_assert(bzt::is_array_v<const double[]>);
    static_assert(bzt::is_array_v<volatile double[5]>);
    static_assert(bzt::is_array_v<const volatile double[]>);
    static_assert(!bzt::is_array_v<std::array<int, 5>>);
}

[[maybe_unused]] void test_is_pointer() {
    static_assert(!bzt::is_pointer_v<Tp>);
    static_assert(bzt::is_pointer_v<Tp*>);
    static_assert(bzt::is_pointer_v<Tp const *volatile>);
    static_assert(bzt::is_pointer_v<Tp const *>);
    static_assert(bzt::is_pointer_v<Tp volatile *>);
    static_assert(!bzt::is_pointer_v<Tp&>);
    static_assert(!bzt::is_pointer_v<Tp const &>);
    static_assert(!bzt::is_pointer_v<int>);
    static_assert(bzt::is_pointer_v<int *>);
    static_assert(bzt::is_pointer_v<int **>);
    static_assert(!bzt::is_pointer_v<int[10]>);
    static_assert(bzt::is_pointer_v<std::decay_t<int[10]>>);
    static_assert(!bzt::is_pointer_v<std::nullptr_t>);
}

[[maybe_unused]] void test_is_lvalue_reference() {
    static_assert(!bzt::is_lvalue_reference_v<Tp>);
    static_assert(bzt::is_lvalue_reference_v<Tp&>);
    static_assert(!bzt::is_lvalue_reference_v<Tp&&>);
    static_assert(!bzt::is_lvalue_reference_v<int>);
    static_assert(bzt::is_lvalue_reference_v<Tp&>);
    static_assert(!bzt::is_lvalue_reference_v<Tp&&>);
    static_assert(!bzt::is_lvalue_reference_v<Tp[]>);
    static_assert(!bzt::is_lvalue_reference_v<Tp[50]>);
    static_assert(bzt::is_lvalue_reference_v<Tp*&>);
    static_assert(bzt::is_lvalue_reference_v<std::nullptr_t &>);
}

[[maybe_unused]] void test_is_rvalue_reference() {
    static_assert(!bzt::is_rvalue_reference_v<Tp>);
    static_assert(!bzt::is_rvalue_reference_v<Tp&>);
    static_assert(bzt::is_rvalue_reference_v<Tp&&>);
    static_assert(!bzt::is_rvalue_reference_v<int>);
    static_assert(!bzt::is_rvalue_reference_v<Tp&>);
    static_assert(bzt::is_rvalue_reference_v<Tp&&>);
    static_assert(!bzt::is_rvalue_reference_v<Tp[]>);
    static_assert(!bzt::is_rvalue_reference_v<Tp[50]>);
    static_assert(bzt::is_rvalue_reference_v<Tp*&&>);
    static_assert(bzt::is_rvalue_reference_v<std::nullptr_t &&>);
}

[[maybe_unused]] void test_is_reference() {
    static_assert(!bzt::is_reference_v<Tp>);
    static_assert(bzt::is_reference_v<Tp&>);
    static_assert(bzt::is_reference_v<Tp&&>);
    static_assert(!bzt::is_reference_v<long>);
    static_assert(bzt::is_reference_v<long&>);
    static_assert(bzt::is_reference_v<long&&>);
    static_assert(!bzt::is_reference_v<double*>);
    static_assert(bzt::is_reference_v<double*&>);
    static_assert(bzt::is_reference_v<double*&&>);
}

namespace {
struct A {
    [[maybe_unused]] [[nodiscard]] int fun() const&{ return 0;};
};

template<typename>
struct PM_traits {};

template<typename T, typename U>
struct PM_traits<U T::*> {
    using member_type = U;
};

    [[maybe_unused]] int f();
}
[[maybe_unused]] void test_is_function() {
    static_assert(!bzt::is_function_v<Tp>);
    static_assert(bzt::is_function_v<int(int)>);
    static_assert(bzt::is_function_v<decltype(f)>);
    static_assert(!bzt::is_function_v<int>);
    using MemberType = PM_traits<decltype(&A::fun)>::member_type;
    static_assert(bzt::is_function_v<MemberType>);
}

[[maybe_unused]] void test_is_member_pointer() {
    static_assert(bzt::is_member_pointer_v<int(Tp::*)>);
    static_assert(!bzt::is_member_pointer_v<int>);
    static_assert(!bzt::is_member_pointer_v<int*>);
    static_assert(bzt::is_member_pointer_v<short(Tp::*)>);
    static_assert(bzt::is_member_pointer_v<float(Tp::*)>);
    static_assert(bzt::is_member_pointer_v<A(Tp::*)>);
    static_assert(bzt::is_member_pointer_v<std::nullptr_t(Tp::*)>);
    static_assert(bzt::is_member_pointer_v<decltype(f)(Tp::*)>);
}

[[maybe_unused]] void test_is_member_object_pointer() {
    static_assert(bzt::is_member_object_pointer_v<int(Tp::*)>);
    static_assert(std::is_member_object_pointer_v<int(Tp::*)>);
    static_assert(!std::is_member_object_pointer_v<int(Tp::*)()>);
    static_assert(!bzt::is_member_object_pointer_v<int(Tp::*)()>);
    static_assert(bzt::is_member_object_pointer_v<Tp(Tp::*)>);
    static_assert(std::is_member_object_pointer_v<Tp(Tp::*)>);
}

namespace
{
    class  MemberFunctionPointer{
    public:
        [[maybe_unused]] void member() { }
    };
}

[[maybe_unused]] void test_is_member_function_pointer() {
    static_assert(!bzt::is_member_function_pointer_v<int>);
    static_assert(!bzt::is_member_function_pointer_v<int[]>);
    static_assert(!bzt::is_member_function_pointer_v<int[18]>);
    static_assert(!bzt::is_member_function_pointer_v<int(Tp::*)>);
    static_assert(bzt::is_member_function_pointer_v<int(Tp::*)()>);
    static_assert(bzt::is_member_function_pointer_v<decltype(&MemberFunctionPointer::member)>);
}

[[maybe_unused]] void test_is_union() {
    struct StructType {};
    typedef union {
        int a;
        float b;
    } UnionType;
    struct StructWithUnionMemberType {
        UnionType d;
    };
    static_assert(!bzt::is_union_v<StructType>);
    static_assert(bzt::is_union_v<UnionType>);
    static_assert(!bzt::is_union_v<StructWithUnionMemberType>);
    static_assert(!bzt::is_union_v<int>);
}

[[maybe_unused]] void test_is_class() {
    struct StructureType {};
    class ClassType {};
    enum class EnumClassType {};
    union UnionType { class [[maybe_unused]] UnionClassMemberType {}; };
    static_assert(!bzt::is_class_v<UnionType>);
    static_assert(bzt::is_class_v<UnionType::UnionClassMemberType>);
    static_assert(bzt::is_class_v<StructureType>);
    static_assert(bzt::is_class_v<ClassType>);
    static_assert(!bzt::is_class_v<ClassType*>);
    static_assert(!bzt::is_class_v<ClassType&>);
    static_assert(bzt::is_class_v<const ClassType>);
    static_assert(!bzt::is_class_v<EnumClassType>);
    static_assert(!bzt::is_class_v<int>);
    static_assert(bzt::is_class_v<struct ImcompleteStructType>);
    static_assert(bzt::is_class_v<class ImcompleteClassType>);
}

[[maybe_unused]] void test_is_enum() {
    struct StructType { enum EnumMember { }; };
    enum EnumType {};
    enum class ScopedEnumType : int {};
    static_assert(!bzt::is_enum_v<StructType>);
    static_assert(bzt::is_enum_v<EnumType>);
    static_assert(bzt::is_enum_v<StructType::EnumMember>);
    static_assert(!bzt::is_enum_v<int>);
    static_assert(bzt::is_enum_v<ScopedEnumType>);
}

[[maybe_unused]] void test_is_complete() {
    class CompleteClassType {};
    class CompleteStructType {};
    static_assert(bzt::is_complete_v<CompleteClassType>);
    static_assert(bzt::is_complete_v<CompleteStructType>);
    static_assert(bzt::is_complete_v<decltype(f)>);
    static_assert(bzt::is_complete_v<decltype(&MemberFunctionPointer::member)>);
    static_assert(!bzt::is_complete_v<struct IncompleteType>);
    static_assert(!bzt::is_complete_v<class IncompleteType>);
}

[[maybe_unused]] void test_is_fundamental() {
    static_assert(!bzt::is_fundamental_v<Tp>);
    static_assert(bzt::is_fundamental_v<int>);
    static_assert(!bzt::is_fundamental_v<int&>);
    static_assert(!bzt::is_fundamental_v<int*>);
    static_assert(bzt::is_fundamental_v<float>);
    static_assert(!bzt::is_fundamental_v<float&>);
    static_assert(!bzt::is_fundamental_v<float*>);
    static_assert(bzt::is_fundamental_v<std::nullptr_t>);
    static_assert(bzt::is_fundamental_v<void>);
    static_assert(bzt::is_fundamental_v<const void>);
    static_assert(bzt::is_fundamental_v<volatile void>);
    static_assert(bzt::is_fundamental_v<const volatile void>);
    static_assert(!bzt::is_fundamental_v<Tp[]>);
    static_assert(!bzt::is_fundamental_v<Tp[5]>);
}

[[maybe_unused]] void test_is_scalar() {
    struct StructType { enum EnumMember { }; };
    enum EnumType {};
    enum class ScopedEnumType : int {};
    static_assert(bzt::is_scalar_v<int>);
    static_assert(bzt::is_scalar_v<float>);
    static_assert(bzt::is_scalar_v<decltype(45)>);
    static_assert(bzt::is_scalar_v<decltype(4.3)>);
    static_assert(bzt::is_scalar_v<decltype(35.5f)>);
    static_assert(bzt::is_scalar_v<decltype(&MemberFunctionPointer::member)>);
    static_assert(bzt::is_scalar_v<A(Tp::*)>);
    static_assert(bzt::is_scalar_v<std::nullptr_t(Tp::*)>);
    static_assert(bzt::is_scalar_v<decltype(f)(Tp::*)>);
    static_assert(bzt::is_scalar_v<decltype(nullptr)>);
    static_assert(bzt::is_scalar_v<std::nullptr_t>);
    static_assert(bzt::is_scalar_v<EnumType>);
    static_assert(bzt::is_scalar_v<StructType::EnumMember>);
    static_assert(bzt::is_scalar_v<ScopedEnumType>);
    static_assert(bzt::is_scalar_v<Tp*>);
    static_assert(bzt::is_scalar_v<Tp const *volatile>);
    static_assert(bzt::is_scalar_v<Tp const *>);
    static_assert(bzt::is_scalar_v<Tp volatile *>);
    static_assert(!bzt::is_scalar_v<Tp>);
}

[[maybe_unused]] void test_is_object() {
    static_assert(bzt::is_object_v<int>);
    static_assert(!bzt::is_object_v<int &>);
    static_assert(bzt::is_object_v<Tp>);
    static_assert(!bzt::is_object_v<Tp &>);
    static_assert(!bzt::is_object_v<const void>);
    static_assert(!bzt::is_object_v<volatile void>);
    static_assert(!bzt::is_object_v<const volatile void>);
    static_assert(!bzt::is_object_v<decltype(f)>);
    static_assert(bzt::is_object_v<decltype(&MemberFunctionPointer::member)>);
    static_assert(bzt::is_object_v<int(Tp::*)>);
}

[[maybe_unused]] void test_is_compound() {
    struct StructType { enum EnumMember { }; };
    enum EnumType {};
    enum class ScopedEnumType : int {};
    class ClassType {};
    static_assert(bzt::is_compound_v<Tp>);
    static_assert(bzt::is_compound_v<Tp[]>);
    static_assert(bzt::is_compound_v<Tp[5]>);
    static_assert(bzt::is_compound_v<float[]>);
    static_assert(bzt::is_compound_v<float[55]>);
    static_assert(bzt::is_compound_v<decltype(f)>);
    static_assert(bzt::is_compound_v<decltype(&MemberFunctionPointer::member)>);
    static_assert(bzt::is_compound_v<int(Tp::*)>);
    static_assert(bzt::is_compound_v<Tp&>);
    static_assert(bzt::is_compound_v<Tp&&>);
    static_assert(bzt::is_compound_v<ClassType>);
    static_assert(bzt::is_compound_v<StructType>);
    static_assert(bzt::is_compound_v<EnumType>);
    static_assert(bzt::is_compound_v<StructType::EnumMember>);
}

[[maybe_unused]] void test_is_remove_pointer() {
    static_assert(std::is_same_v<int, bzt::remove_pointer_t<int*>>);
    static_assert(std::is_same_v<int*, bzt::remove_pointer_t<int**>>);
    static_assert(std::is_same_v<int**, bzt::remove_pointer_t<int***>>);
    static_assert(std::is_same_v<int***, bzt::remove_pointer_t<int****>>);
    static_assert(std::is_same_v<int****, bzt::remove_pointer_t<int*****>>);
    static_assert(std::is_same_v<const int, bzt::remove_pointer_t<const int*>>);
    static_assert(std::is_same_v<const int*, bzt::remove_pointer_t<const int**>>);
    static_assert(std::is_same_v<int, bzt::remove_pointer_t<int* const >>);
    static_assert(std::is_same_v<int, bzt::remove_pointer_t<int* volatile>>);
    static_assert(std::is_same_v<int, bzt::remove_pointer_t<int* const volatile>>);
    static_assert(std::is_same_v<int, bzt::remove_pointer_t<int* const >>);
    static_assert(std::is_same_v<int*, bzt::remove_pointer_t<int** const >>);
    static_assert(std::is_same_v<int**, bzt::remove_pointer_t<int*** const >>);
    static_assert(std::is_same_v<int***, bzt::remove_pointer_t<int**** const >>);
    static_assert(std::is_same_v<int****, bzt::remove_pointer_t<int***** const >>);
    static_assert(std::is_same_v<int, bzt::remove_pointer_t<int* volatile>>);
    static_assert(std::is_same_v<int*, bzt::remove_pointer_t<int** volatile>>);
    static_assert(std::is_same_v<int**, bzt::remove_pointer_t<int*** volatile>>);
    static_assert(std::is_same_v<int***, bzt::remove_pointer_t<int**** volatile>>);
    static_assert(std::is_same_v<int****, bzt::remove_pointer_t<int***** volatile>>);
    static_assert(std::is_same_v<int, bzt::remove_pointer_t<int* const volatile>>);
    static_assert(std::is_same_v<int*, bzt::remove_pointer_t<int** const volatile>>);
    static_assert(std::is_same_v<int**, bzt::remove_pointer_t<int*** const volatile>>);
    static_assert(std::is_same_v<int***, bzt::remove_pointer_t<int**** const volatile>>);
    static_assert(std::is_same_v<int****, bzt::remove_pointer_t<int***** const volatile>>);
}

[[maybe_unused]] void test_is_add_pointer() {


}

int main() {return EXIT_SUCCESS;}
