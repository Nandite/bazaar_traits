// Copyright (c) 2022 Papa Libasse Sow.
// https://github.com/Nandite/bazaar_traits
// Distributed under the MIT Software License (X11 license).
//
// SPDX-License-Identifier: MIT
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of
// the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <utility>
#include <array>
#include "bazaar_traits.hpp"
#include "arithmetic.hpp"
#include "classes.hpp"

namespace bzt = bazaar::traits;

[[maybe_unused]] void test_rank() {
    static_assert(0 == bzt::rank_v<int>);
    static_assert(1 == bzt::rank_v<int[5]>);
    static_assert(2 == bzt::rank_v<int[5][5]>);
    static_assert(3 == bzt::rank_v<int[][5][5]>);

    [[maybe_unused]] int ary[][3]={};
    static_assert(0 == bzt::rank_v<decltype(ary[0])>);
    static_assert(bzt::is_same_v<decltype(ary[0]), int(&)[3]>);
    static_assert(1 == bzt::rank_v<bzt::remove_cvref_t<decltype(ary[0])>>);
}

[[maybe_unused]] void test_extent() {
    static_assert(3 == bzt::extent_v<int[3]>);
    static_assert(3 == bzt::extent_v<int[3][4], 0>);
    static_assert(4 == bzt::extent_v<int[3][4], 1>);
    static_assert(0 == bzt::extent_v<int[3][4], 2>);
    static_assert(0 == bzt::extent_v<int[]>);

    const int ints[] = {1,2,3,4};
    static_assert(4 == bzt::extent_v<decltype(ints)>);

    [[maybe_unused]] int ary[][3]={};
    static_assert(0 == bzt::extent_v<decltype(ary[0])>);
    static_assert(3 == bzt::extent_v<bzt::remove_cvref_t<decltype(ary[0])>>);
}

[[maybe_unused]] void test_remove_extent() {
    static_assert(bzt::is_same_v<std::remove_extent_t<int>, bzt::remove_extent_t<int>>);
    static_assert(bzt::is_same_v<std::remove_extent_t<int[2]>, bzt::remove_extent_t<int[2]>>);
    static_assert(bzt::is_same_v<std::remove_extent_t<Tp>, bzt::remove_extent_t<Tp>>);
    static_assert(bzt::is_same_v<std::remove_extent_t<Tp[2][4]>, bzt::remove_extent_t<Tp[2][4]>>);
    static_assert(bzt::is_same_v<std::remove_extent_t<int[]>, bzt::remove_extent_t<int[]>>);
    static_assert(bzt::is_same_v<std::remove_extent_t<int[2][10]>, bzt::remove_extent_t<int[2][10]>>);
    static_assert(bzt::is_same_v<std::remove_extent_t<int[][6]>, bzt::remove_extent_t<int[][6]>>);
}

[[maybe_unused]] void test_all_remove_extents() {
    static_assert(bzt::is_same_v<std::remove_all_extents_t<float>, bzt::remove_all_extents_t<float>>);
    static_assert(bzt::is_same_v<std::remove_all_extents_t<float[1][2][3]>, bzt::remove_all_extents_t<float[1][2][3]>>);
    static_assert(bzt::is_same_v<std::remove_all_extents_t<float [1][1][1][1][2]>,
            bzt::remove_all_extents_t<float [1][1][1][1][2]>>);
    static_assert(bzt::is_same_v<std::remove_all_extents_t<float*>, bzt::remove_all_extents_t<float*>>);
    static_assert(bzt::is_same_v<std::remove_all_extents_t<int[3][2]>, bzt::remove_all_extents_t<int[3][2]>>);
    static_assert(bzt::is_same_v<std::remove_all_extents_t<double[2][3]>, bzt::remove_all_extents_t<double[2][3]>>);
    struct X { int m; };
    static_assert(bzt::is_same_v<std::remove_all_extents_t<X[3][3]>, bzt::remove_all_extents_t<X[3][3]>>);
}

[[maybe_unused]] void test_is_bounded_array() {
    static_assert(!bzt::is_bounded_array_v<Tp>);
    static_assert(!bzt::is_bounded_array_v<Tp[]>);
    static_assert(bzt::is_bounded_array_v<Tp[3]>);
    static_assert(!bzt::is_bounded_array_v<float>);
    static_assert(!bzt::is_bounded_array_v<int>);
    static_assert(!bzt::is_bounded_array_v<int[]>);
    static_assert(bzt::is_bounded_array_v<int[3]>);
}

[[maybe_unused]] void test_is_unbounded_array() {
    static_assert(!bzt::is_unbounded_array_v<Tp>);
    static_assert(bzt::is_unbounded_array_v<Tp[]>);
    static_assert(!bzt::is_unbounded_array_v<Tp[3]>);
    static_assert(!bzt::is_unbounded_array_v<float>);
    static_assert(!bzt::is_unbounded_array_v<int>);
    static_assert(bzt::is_unbounded_array_v<int[]>);
    static_assert(!bzt::is_unbounded_array_v<int[3]>);
}

[[maybe_unused]] void test_remove_reference() {
    static_assert(bzt::is_same_v<int, bzt::remove_reference_t<int>>);
    static_assert(bzt::is_same_v<int, bzt::remove_reference_t<int&>>);
    static_assert(bzt::is_same_v<int, bzt::remove_reference_t<int&&>>);

    static_assert(bzt::is_same_v<const int, bzt::remove_reference_t<const int>>);
    static_assert(bzt::is_same_v<const int, bzt::remove_reference_t<const int&>>);
    static_assert(bzt::is_same_v<const int, bzt::remove_reference_t<const int&&>>);

    static_assert(bzt::is_same_v<volatile int, bzt::remove_reference_t<volatile int>>);
    static_assert(bzt::is_same_v<volatile int, bzt::remove_reference_t<volatile int&>>);
    static_assert(bzt::is_same_v<volatile int, bzt::remove_reference_t<volatile int&&>>);

    static_assert(bzt::is_same_v<const volatile int, bzt::remove_reference_t<const volatile int>>);
    static_assert(bzt::is_same_v<const volatile int, bzt::remove_reference_t<const volatile int&>>);
    static_assert(bzt::is_same_v<const volatile int, bzt::remove_reference_t<const volatile int&&>>);

    static_assert(bzt::is_same_v<int*, bzt::remove_reference_t<int*>>);
    static_assert(bzt::is_same_v<int**, bzt::remove_reference_t<int**>>);
    static_assert(bzt::is_same_v<int[], bzt::remove_reference_t<int[]>>);
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
    static_assert(bzt::is_same_v<bzt::remove_cv_t<int>, int>);
    static_assert(bzt::is_same_v<bzt::remove_cv_t<volatile int >, int >);
    static_assert(bzt::is_same_v<bzt::remove_cv_t<const volatile int >, int>);
    static_assert(bzt::is_same_v<bzt::remove_cv_t<const volatile int* >, const volatile int* >);
    static_assert(bzt::is_same_v<bzt::remove_cv_t<const int* volatile >, const int* >);
    static_assert(bzt::is_same_v<bzt::remove_cv_t< int* const volatile >, int* >);

    using type1 = bzt::remove_cv<const int>::type;
    using type2 = bzt::remove_cv<volatile int>::type;
    using type3 = bzt::remove_cv<const volatile int>::type;
    using type4 = bzt::remove_cv<const volatile int*>::type;
    using type5 = bzt::remove_cv<int* const volatile>::type;

    static_assert(bzt::is_same_v<type1, int>);
    static_assert(bzt::is_same_v<type2, int>);
    static_assert(bzt::is_same_v<type3, int>);
    static_assert(!bzt::is_same_v<type4, int*>);
    static_assert(bzt::is_same_v<type4, const volatile int*>);
    static_assert(bzt::is_same_v<type5, int*>);
}

[[maybe_unused]] void test_add_const_volatile_and_cv() {
    static_assert(bzt::is_same_v<bzt::add_const_t<int>, const int>);
    static_assert(bzt::is_same_v<bzt::add_const_t<const int>, const int>);
    static_assert(bzt::is_same_v<bzt::add_const_t<Tp>, const Tp>);
    static_assert(bzt::is_same_v<bzt::add_const_t<int *>, int * const>);
    static_assert(bzt::is_same_v<bzt::add_const_t<int[]>, const int[]>);
    static_assert(bzt::is_same_v<bzt::add_const_t<int&>, int &>);
    static_assert(bzt::is_same_v<bzt::add_const_t<int**>, int** const>);

    static_assert(bzt::is_same_v<bzt::add_volatile_t<int>, volatile int>);
    static_assert(bzt::is_same_v<bzt::add_volatile_t<volatile int>, volatile  int>);
    static_assert(bzt::is_same_v<bzt::add_volatile_t<Tp>, volatile Tp>);
    static_assert(bzt::is_same_v<bzt::add_volatile_t<int *>, int * volatile>);
    static_assert(bzt::is_same_v<bzt::add_volatile_t<int[]>, volatile int[]>);
    static_assert(bzt::is_same_v<bzt::add_volatile_t<int&>, int &>);
    static_assert(bzt::is_same_v<bzt::add_volatile_t<int**>, int** volatile>);

    static_assert(bzt::is_same_v<bzt::add_cv_t<int>, const volatile int>);
    static_assert(bzt::is_same_v<bzt::add_cv_t<Tp>, const volatile Tp>);
    static_assert(bzt::is_same_v<bzt::add_cv_t<int *>, int * const volatile>);
    static_assert(bzt::is_same_v<bzt::add_cv_t<int[]>, const volatile int[]>);
    static_assert(bzt::is_same_v<bzt::add_cv_t<int&>, int &>);
    static_assert(bzt::is_same_v<bzt::add_cv_t<int**>, int** const volatile>);
    static_assert(bzt::is_same_v<bzt::add_cv_t<int**>, int** volatile const >);
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

    static_assert(!bzt::is_union_v<EmptyStructType>);
    static_assert(bzt::is_union_v<UnionType>);
    static_assert(!bzt::is_union_v<StructWithUnionMemberType>);
    static_assert(!bzt::is_union_v<int>);
}

[[maybe_unused]] void test_is_class() {
    static_assert(!bzt::is_class_v<UnionTypeWithClassMember>);
    static_assert(bzt::is_class_v<UnionTypeWithClassMember::UnionClassMemberType>);
    static_assert(bzt::is_class_v<EmptyStructType>);
    static_assert(bzt::is_class_v<EmptyClassType>);
    static_assert(!bzt::is_class_v<EmptyClassType*>);
    static_assert(!bzt::is_class_v<EmptyClassType&>);
    static_assert(bzt::is_class_v<const EmptyClassType>);
    static_assert(!bzt::is_class_v<EnumClassType>);
    static_assert(!bzt::is_class_v<int>);
    static_assert(bzt::is_class_v<struct ImcompleteStructType>);
    static_assert(bzt::is_class_v<class ImcompleteClassType>);
}

[[maybe_unused]] void test_is_enum() {
    static_assert(!bzt::is_enum_v<StructTypeWithEnumMember>);
    static_assert(bzt::is_enum_v<EnumType>);
    static_assert(bzt::is_enum_v<StructTypeWithEnumMember::EnumMember>);
    static_assert(!bzt::is_enum_v<int>);
    static_assert(bzt::is_enum_v<EnumClassWithSignedUnderlyingType>);
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
    static_assert(bzt::is_compound_v<EmptyClassType>);
    static_assert(bzt::is_compound_v<EmptyStructType>);
    static_assert(bzt::is_compound_v<EnumType>);
    static_assert(bzt::is_compound_v<StructTypeWithEnumMember::EnumMember>);
}

[[maybe_unused]] void test_is_remove_pointer() {
    static_assert(bzt::is_same_v<int, bzt::remove_pointer_t<int*>>);
    static_assert(bzt::is_same_v<int*, bzt::remove_pointer_t<int**>>);
    static_assert(bzt::is_same_v<int**, bzt::remove_pointer_t<int***>>);
    static_assert(bzt::is_same_v<int***, bzt::remove_pointer_t<int****>>);
    static_assert(bzt::is_same_v<int****, bzt::remove_pointer_t<int*****>>);
    static_assert(bzt::is_same_v<const int, bzt::remove_pointer_t<const int*>>);
    static_assert(bzt::is_same_v<const int*, bzt::remove_pointer_t<const int**>>);
    static_assert(bzt::is_same_v<int, bzt::remove_pointer_t<int* const >>);
    static_assert(bzt::is_same_v<int, bzt::remove_pointer_t<int* volatile>>);
    static_assert(bzt::is_same_v<int, bzt::remove_pointer_t<int* const volatile>>);
    static_assert(bzt::is_same_v<int, bzt::remove_pointer_t<int* const >>);
    static_assert(bzt::is_same_v<int*, bzt::remove_pointer_t<int** const >>);
    static_assert(bzt::is_same_v<int**, bzt::remove_pointer_t<int*** const >>);
    static_assert(bzt::is_same_v<int***, bzt::remove_pointer_t<int**** const >>);
    static_assert(bzt::is_same_v<int****, bzt::remove_pointer_t<int***** const >>);
    static_assert(bzt::is_same_v<int, bzt::remove_pointer_t<int* volatile>>);
    static_assert(bzt::is_same_v<int*, bzt::remove_pointer_t<int** volatile>>);
    static_assert(bzt::is_same_v<int**, bzt::remove_pointer_t<int*** volatile>>);
    static_assert(bzt::is_same_v<int***, bzt::remove_pointer_t<int**** volatile>>);
    static_assert(bzt::is_same_v<int****, bzt::remove_pointer_t<int***** volatile>>);
    static_assert(bzt::is_same_v<int, bzt::remove_pointer_t<int* const volatile>>);
    static_assert(bzt::is_same_v<int*, bzt::remove_pointer_t<int** const volatile>>);
    static_assert(bzt::is_same_v<int**, bzt::remove_pointer_t<int*** const volatile>>);
    static_assert(bzt::is_same_v<int***, bzt::remove_pointer_t<int**** const volatile>>);
    static_assert(bzt::is_same_v<int****, bzt::remove_pointer_t<int***** const volatile>>);
}

[[maybe_unused]] void test_is_add_pointer() {
    static_assert(bzt::is_same_v<int*, bzt::add_pointer_t<int>>);
    static_assert(bzt::is_same_v<int*, bzt::add_pointer_t<int&>>);
    static_assert(bzt::is_same_v<int*, bzt::add_pointer_t<int&&>>);
    static_assert(bzt::is_same_v<void*, bzt::add_pointer_t<void>>);
    static_assert(bzt::is_same_v<int, bzt::remove_pointer_t<bzt::add_pointer_t<int>>>);
    static_assert(bzt::is_same_v<int, bzt::remove_pointer_t<bzt::add_pointer_t<int&>>>);
    static_assert(bzt::is_same_v<int, bzt::remove_pointer_t<bzt::add_pointer_t<int&&>>>);
    static_assert(bzt::is_same_v<void, bzt::remove_pointer_t<bzt::add_pointer_t<void>>>);
    static_assert(bzt::is_same_v<Tp*, bzt::add_pointer_t<Tp>>);
    static_assert(bzt::is_same_v<const int*, bzt::add_pointer_t<const int>>);
    static_assert(bzt::is_same_v<volatile int*, bzt::add_pointer_t<volatile int>>);
    static_assert(bzt::is_same_v<const volatile int*, bzt::add_pointer_t<const volatile int>>);
}

[[maybe_unused]] void test_is_signed() {
    static_assert(!bzt::is_signed_v<Tp>);
    static_assert(bzt::is_signed_v<float>);
    static_assert(bzt::is_signed_v<signed int>);
    static_assert(!bzt::is_signed_v<unsigned int>);
    static_assert(bzt::is_signed_v<signed int>);
    static_assert(!bzt::is_signed_v<unsigned int>);
    static_assert(!bzt::is_signed_v<EnumType>);
    static_assert(!bzt::is_signed_v<EnumClassType>);
    static_assert(bzt::is_signed_v<std::underlying_type_t<EnumClassWithSignedUnderlyingType>>);
    static_assert(!bzt::is_signed_v<std::underlying_type_t<EnumClassWithUnsignedUnderlyingType>>);
    static_assert(!bzt::is_signed_v<bool>);
}

[[maybe_unused]] void test_is_unsigned() {
    static_assert(!bzt::is_unsigned_v<Tp>);
    static_assert(!bzt::is_unsigned_v<float>);
    static_assert(!bzt::is_unsigned_v<signed int>);
    static_assert(bzt::is_unsigned_v<unsigned int>);
    static_assert(!bzt::is_unsigned_v<EnumType>);
    static_assert(!bzt::is_unsigned_v<EnumClassType>);
    static_assert(!bzt::is_unsigned_v<std::underlying_type_t<EnumClassWithSignedUnderlyingType>>);
    static_assert(bzt::is_unsigned_v<std::underlying_type_t<EnumClassWithUnsignedUnderlyingType>>);
    static_assert(bzt::is_unsigned_v<bool>);
}

[[maybe_unused]] void test_make_signed() {
    static_assert(bzt::is_same_v<signed char, std::make_signed_t<signed char>>);
    static_assert(bzt::is_same_v<signed char, bzt::make_signed_t<unsigned char>>);
    static_assert(bzt::is_same_v<signed short, bzt::make_signed_t<signed short>>);
    static_assert(bzt::is_same_v<signed short, bzt::make_signed_t<unsigned short>>);
    static_assert(bzt::is_same_v<signed int, bzt::make_signed_t<signed int>>);
    static_assert(bzt::is_same_v<signed int, bzt::make_signed_t<unsigned int>>);
    static_assert(bzt::is_same_v<signed long, bzt::make_signed_t<signed long>>);
    static_assert(bzt::is_same_v<signed long, bzt::make_signed_t<unsigned long>>);
    static_assert(bzt::is_same_v<signed long long, bzt::make_signed_t<signed long long>>);
    static_assert(bzt::is_same_v<signed long long, bzt::make_signed_t<unsigned long long>>);

    static_assert(bzt::is_same_v<const signed char, bzt::make_signed_t<const signed char>>);
    static_assert(bzt::is_same_v<const signed char, bzt::make_signed_t<const unsigned char>>);
    static_assert(bzt::is_same_v<const signed short, bzt::make_signed_t<const signed short>>);
    static_assert(bzt::is_same_v<const signed short, bzt::make_signed_t<const unsigned short>>);
    static_assert(bzt::is_same_v<const signed int, bzt::make_signed_t<const signed int>>);
    static_assert(bzt::is_same_v<const signed int, bzt::make_signed_t<const unsigned int>>);
    static_assert(bzt::is_same_v<const signed long, bzt::make_signed_t<const signed long>>);
    static_assert(bzt::is_same_v<const signed long, bzt::make_signed_t<const unsigned long>>);
    static_assert(bzt::is_same_v<const signed long long, bzt::make_signed_t<const signed long long>>);
    static_assert(bzt::is_same_v<const signed long long, bzt::make_signed_t<const unsigned long long>>);

    static_assert(bzt::is_same_v<volatile signed char, bzt::make_signed_t<volatile signed char>>);
    static_assert(bzt::is_same_v<volatile signed char, bzt::make_signed_t<volatile unsigned char>>);
    static_assert(bzt::is_same_v<volatile signed short, bzt::make_signed_t<volatile signed short>>);
    static_assert(bzt::is_same_v<volatile signed short, bzt::make_signed_t<volatile unsigned short>>);
    static_assert(bzt::is_same_v<volatile signed int, bzt::make_signed_t<volatile signed int>>);
    static_assert(bzt::is_same_v<volatile signed int, bzt::make_signed_t<volatile unsigned int>>);
    static_assert(bzt::is_same_v<volatile signed long, bzt::make_signed_t<volatile signed long>>);
    static_assert(bzt::is_same_v<volatile signed long, bzt::make_signed_t<volatile unsigned long>>);
    static_assert(bzt::is_same_v<volatile signed long long, bzt::make_signed_t<volatile signed long long>>);
    static_assert(bzt::is_same_v<volatile signed long long, bzt::make_signed_t<volatile unsigned long long>>);

    static_assert(bzt::is_same_v<const volatile signed char, bzt::make_signed_t<const volatile signed char>>);
    static_assert(bzt::is_same_v<const volatile signed char, bzt::make_signed_t<const volatile unsigned char>>);
    static_assert(bzt::is_same_v<const volatile signed short, bzt::make_signed_t<const volatile signed short>>);
    static_assert(bzt::is_same_v<const volatile signed short, bzt::make_signed_t<const volatile unsigned short>>);
    static_assert(bzt::is_same_v<const volatile signed int, bzt::make_signed_t<const volatile signed int>>);
    static_assert(bzt::is_same_v<const volatile signed int, bzt::make_signed_t<const volatile unsigned int>>);
    static_assert(bzt::is_same_v<const volatile signed long, bzt::make_signed_t<const volatile signed long>>);
    static_assert(bzt::is_same_v<const volatile signed long, bzt::make_signed_t<const volatile unsigned long>>);
    static_assert(bzt::is_same_v<const volatile signed long long, bzt::make_signed_t<const volatile signed long long>>);
    static_assert(bzt::is_same_v<const volatile signed long long, bzt::make_signed_t<const volatile unsigned long long>>);

    static_assert(bzt::is_same_v<signed char, bzt::make_signed_t<EnumWithUnderlyingChar>>);
    static_assert(bzt::is_same_v<signed char, bzt::make_signed_t<EnumWithUnderlyingUChar>>);
    static_assert(bzt::is_same_v<signed short, bzt::make_signed_t<EnumWithUnderlyingShort>>);
    static_assert(bzt::is_same_v<signed short, bzt::make_signed_t<EnumWithUnderlyingUShort>>);
    static_assert(bzt::is_same_v<signed int, bzt::make_signed_t<EnumWithUnderlyingInt>>);
    static_assert(bzt::is_same_v<signed int, bzt::make_signed_t<EnumWithUnderlyingUInt>>);
    static_assert(bzt::is_same_v<signed long, bzt::make_signed_t<EnumWithUnderlyingLong>>);
    static_assert(bzt::is_same_v<signed long, bzt::make_signed_t<EnumWithUnderlyingULong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            signed long, signed long long>,
            bzt::make_signed_t<EnumWithUnderlyingLongLong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            signed long, signed long long>,
            bzt::make_signed_t<EnumWithUnderlyingULongLong>>);

    static_assert(bzt::is_same_v<const signed char, bzt::make_signed_t<const EnumWithUnderlyingChar>>);
    static_assert(bzt::is_same_v<const signed char, bzt::make_signed_t<const EnumWithUnderlyingUChar>>);
    static_assert(bzt::is_same_v<const signed short, bzt::make_signed_t<const EnumWithUnderlyingShort>>);
    static_assert(bzt::is_same_v<const signed short, bzt::make_signed_t<const EnumWithUnderlyingUShort>>);
    static_assert(bzt::is_same_v<const signed int, bzt::make_signed_t<const EnumWithUnderlyingInt>>);
    static_assert(bzt::is_same_v<const signed int, bzt::make_signed_t<const EnumWithUnderlyingUInt>>);
    static_assert(bzt::is_same_v<const signed long, bzt::make_signed_t<const EnumWithUnderlyingLong>>);
    static_assert(bzt::is_same_v<const signed long, bzt::make_signed_t<const EnumWithUnderlyingULong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            const signed long, const signed long long>,
            bzt::make_signed_t<const EnumWithUnderlyingLongLong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            const signed long, const signed long long>,
            bzt::make_signed_t<const EnumWithUnderlyingULongLong>>);

    static_assert(bzt::is_same_v<volatile signed char, bzt::make_signed_t<volatile EnumWithUnderlyingChar>>);
    static_assert(bzt::is_same_v<volatile signed char, bzt::make_signed_t<volatile EnumWithUnderlyingUChar>>);
    static_assert(bzt::is_same_v<volatile signed short, bzt::make_signed_t<volatile EnumWithUnderlyingShort>>);
    static_assert(bzt::is_same_v<volatile signed short, bzt::make_signed_t<volatile EnumWithUnderlyingUShort>>);
    static_assert(bzt::is_same_v<volatile signed int, bzt::make_signed_t<volatile EnumWithUnderlyingInt>>);
    static_assert(bzt::is_same_v<volatile signed int, bzt::make_signed_t<volatile EnumWithUnderlyingUInt>>);
    static_assert(bzt::is_same_v<volatile signed long, bzt::make_signed_t<volatile EnumWithUnderlyingLong>>);
    static_assert(bzt::is_same_v<volatile signed long, bzt::make_signed_t<volatile EnumWithUnderlyingULong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            volatile signed long, volatile signed long long>,
            bzt::make_signed_t<volatile EnumWithUnderlyingLongLong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            volatile signed long, volatile signed long long>,
            bzt::make_signed_t<volatile EnumWithUnderlyingULongLong>>);

    static_assert(bzt::is_same_v<const volatile signed char, bzt::make_signed_t<const volatile EnumWithUnderlyingChar>>);
    static_assert(bzt::is_same_v<const volatile signed char, bzt::make_signed_t<const volatile EnumWithUnderlyingUChar>>);
    static_assert(bzt::is_same_v<const volatile signed short, bzt::make_signed_t<const volatile EnumWithUnderlyingShort>>);
    static_assert(bzt::is_same_v<const volatile signed short, bzt::make_signed_t<const volatile EnumWithUnderlyingUShort>>);
    static_assert(bzt::is_same_v<const volatile signed int, bzt::make_signed_t<const volatile EnumWithUnderlyingInt>>);
    static_assert(bzt::is_same_v<const volatile signed int, bzt::make_signed_t<const volatile EnumWithUnderlyingUInt>>);
    static_assert(bzt::is_same_v<const volatile signed long, bzt::make_signed_t<const volatile EnumWithUnderlyingLong>>);
    static_assert(bzt::is_same_v<const volatile signed long, bzt::make_signed_t<const volatile EnumWithUnderlyingULong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            const volatile signed long, const volatile signed long long>,
            bzt::make_signed_t<const volatile EnumWithUnderlyingLongLong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            const volatile signed long, const volatile signed long long>,
            bzt::make_signed_t<const volatile EnumWithUnderlyingULongLong>>);

#if __cplusplus > 201703L
    static_assert(sizeof(bzt::make_signed_t<char8_t>) == 1);
    static_assert(sizeof(bzt::make_signed_t<const char8_t>) == 1);
    static_assert(sizeof(bzt::make_signed_t<volatile char8_t>) == 1);
    static_assert(sizeof(bzt::make_signed_t<const volatile char8_t>) == 1);
#endif
    static_assert(sizeof(bzt::make_signed_t<char16_t>) == 2);
    static_assert(sizeof(bzt::make_signed_t<const char16_t>) == 2);
    static_assert(sizeof(bzt::make_signed_t<volatile char16_t>) == 2);
    static_assert(sizeof(bzt::make_signed_t<const volatile char16_t>) == 2);
    static_assert(sizeof(bzt::make_signed_t<char32_t>) == 4);
    static_assert(sizeof(bzt::make_signed_t<const char32_t>) == 4);
    static_assert(sizeof(bzt::make_signed_t<volatile char32_t>) == 4);
    static_assert(sizeof(bzt::make_signed_t<const volatile char32_t>) == 4);
    static_assert(sizeof(bzt::make_signed_t<wchar_t>) == 2 ||
                  sizeof(bzt::make_signed_t<wchar_t>) == 4);
    static_assert(sizeof(bzt::make_signed_t<const wchar_t>) == 2 ||
                  sizeof(bzt::make_signed_t<const wchar_t>) == 4);
    static_assert(sizeof(bzt::make_signed_t<volatile wchar_t>) == 2 ||
                  sizeof(bzt::make_signed_t<volatile wchar_t>) == 4);
    static_assert(sizeof(bzt::make_signed_t<const volatile wchar_t>) == 2 ||
                  sizeof(bzt::make_signed_t<const volatile wchar_t>) == 4);
}

[[maybe_unused]] void test_make_unsigned() {
    static_assert(bzt::is_same_v<unsigned char, std::make_unsigned_t<signed char>>);
    static_assert(bzt::is_same_v<unsigned char, bzt::make_unsigned_t<unsigned char>>);
    static_assert(bzt::is_same_v<unsigned short, bzt::make_unsigned_t<signed short>>);
    static_assert(bzt::is_same_v<unsigned short, bzt::make_unsigned_t<unsigned short>>);
    static_assert(bzt::is_same_v<unsigned int, bzt::make_unsigned_t<signed int>>);
    static_assert(bzt::is_same_v<unsigned int, bzt::make_unsigned_t<unsigned int>>);
    static_assert(bzt::is_same_v<unsigned long, bzt::make_unsigned_t<signed long>>);
    static_assert(bzt::is_same_v<unsigned long, bzt::make_unsigned_t<unsigned long>>);
    static_assert(bzt::is_same_v<unsigned long long, bzt::make_unsigned_t<signed long long>>);
    static_assert(bzt::is_same_v<unsigned long long, bzt::make_unsigned_t<unsigned long long>>);

    static_assert(bzt::is_same_v<const unsigned char, bzt::make_unsigned_t<const signed char>>);
    static_assert(bzt::is_same_v<const unsigned char, bzt::make_unsigned_t<const unsigned char>>);
    static_assert(bzt::is_same_v<const unsigned short, bzt::make_unsigned_t<const signed short>>);
    static_assert(bzt::is_same_v<const unsigned short, bzt::make_unsigned_t<const unsigned short>>);
    static_assert(bzt::is_same_v<const unsigned int, bzt::make_unsigned_t<const signed int>>);
    static_assert(bzt::is_same_v<const unsigned int, bzt::make_unsigned_t<const unsigned int>>);
    static_assert(bzt::is_same_v<const unsigned long, bzt::make_unsigned_t<const signed long>>);
    static_assert(bzt::is_same_v<const unsigned long, bzt::make_unsigned_t<const unsigned long>>);
    static_assert(bzt::is_same_v<const unsigned long long, bzt::make_unsigned_t<const signed long long>>);
    static_assert(bzt::is_same_v<const unsigned long long, bzt::make_unsigned_t<const unsigned long long>>);

    static_assert(bzt::is_same_v<volatile unsigned char, bzt::make_unsigned_t<volatile signed char>>);
    static_assert(bzt::is_same_v<volatile unsigned char, bzt::make_unsigned_t<volatile unsigned char>>);
    static_assert(bzt::is_same_v<volatile unsigned short, bzt::make_unsigned_t<volatile signed short>>);
    static_assert(bzt::is_same_v<volatile unsigned short, bzt::make_unsigned_t<volatile unsigned short>>);
    static_assert(bzt::is_same_v<volatile unsigned int, bzt::make_unsigned_t<volatile signed int>>);
    static_assert(bzt::is_same_v<volatile unsigned int, bzt::make_unsigned_t<volatile unsigned int>>);
    static_assert(bzt::is_same_v<volatile unsigned long, bzt::make_unsigned_t<volatile signed long>>);
    static_assert(bzt::is_same_v<volatile unsigned long, bzt::make_unsigned_t<volatile unsigned long>>);
    static_assert(bzt::is_same_v<volatile unsigned long long, bzt::make_unsigned_t<volatile signed long long>>);
    static_assert(bzt::is_same_v<volatile unsigned long long, bzt::make_unsigned_t<volatile unsigned long long>>);

    static_assert(bzt::is_same_v<const volatile unsigned char, bzt::make_unsigned_t<const volatile signed char>>);
    static_assert(bzt::is_same_v<const volatile unsigned char, bzt::make_unsigned_t<const volatile unsigned char>>);
    static_assert(bzt::is_same_v<const volatile unsigned short, bzt::make_unsigned_t<const volatile signed short>>);
    static_assert(bzt::is_same_v<const volatile unsigned short, bzt::make_unsigned_t<const volatile unsigned short>>);
    static_assert(bzt::is_same_v<const volatile unsigned int, bzt::make_unsigned_t<const volatile signed int>>);
    static_assert(bzt::is_same_v<const volatile unsigned int, bzt::make_unsigned_t<const volatile unsigned int>>);
    static_assert(bzt::is_same_v<const volatile unsigned long, bzt::make_unsigned_t<const volatile signed long>>);
    static_assert(bzt::is_same_v<const volatile unsigned long, bzt::make_unsigned_t<const volatile unsigned long>>);
    static_assert(bzt::is_same_v<const volatile unsigned long long, bzt::make_unsigned_t<const volatile signed long long>>);
    static_assert(bzt::is_same_v<const volatile unsigned long long, bzt::make_unsigned_t<const volatile unsigned long long>>);

    static_assert(bzt::is_same_v<unsigned char, bzt::make_unsigned_t<EnumWithUnderlyingChar>>);
    static_assert(bzt::is_same_v<unsigned char, bzt::make_unsigned_t<EnumWithUnderlyingUChar>>);
    static_assert(bzt::is_same_v<unsigned short, bzt::make_unsigned_t<EnumWithUnderlyingShort>>);
    static_assert(bzt::is_same_v<unsigned short, bzt::make_unsigned_t<EnumWithUnderlyingUShort>>);
    static_assert(bzt::is_same_v<unsigned int, bzt::make_unsigned_t<EnumWithUnderlyingInt>>);
    static_assert(bzt::is_same_v<unsigned int, bzt::make_unsigned_t<EnumWithUnderlyingUInt>>);
    static_assert(bzt::is_same_v<unsigned long, bzt::make_unsigned_t<EnumWithUnderlyingLong>>);
    static_assert(bzt::is_same_v<unsigned long, bzt::make_unsigned_t<EnumWithUnderlyingULong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            unsigned long, unsigned long long>,
            bzt::make_unsigned_t<EnumWithUnderlyingLongLong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            unsigned long, unsigned long long>,
            bzt::make_unsigned_t<EnumWithUnderlyingULongLong>>);

    static_assert(bzt::is_same_v<const unsigned char, bzt::make_unsigned_t<const EnumWithUnderlyingChar>>);
    static_assert(bzt::is_same_v<const unsigned char, bzt::make_unsigned_t<const EnumWithUnderlyingUChar>>);
    static_assert(bzt::is_same_v<const unsigned short, bzt::make_unsigned_t<const EnumWithUnderlyingShort>>);
    static_assert(bzt::is_same_v<const unsigned short, bzt::make_unsigned_t<const EnumWithUnderlyingUShort>>);
    static_assert(bzt::is_same_v<const unsigned int, bzt::make_unsigned_t<const EnumWithUnderlyingInt>>);
    static_assert(bzt::is_same_v<const unsigned int, bzt::make_unsigned_t<const EnumWithUnderlyingUInt>>);
    static_assert(bzt::is_same_v<const unsigned long, bzt::make_unsigned_t<const EnumWithUnderlyingLong>>);
    static_assert(bzt::is_same_v<const unsigned long, bzt::make_unsigned_t<const EnumWithUnderlyingULong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            const unsigned long, const unsigned long long>,
            bzt::make_unsigned_t<const EnumWithUnderlyingLongLong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            const unsigned long, const unsigned long long>,
            bzt::make_unsigned_t<const EnumWithUnderlyingULongLong>>);

    static_assert(bzt::is_same_v<volatile unsigned char, bzt::make_unsigned_t<volatile EnumWithUnderlyingChar>>);
    static_assert(bzt::is_same_v<volatile unsigned char, bzt::make_unsigned_t<volatile EnumWithUnderlyingUChar>>);
    static_assert(bzt::is_same_v<volatile unsigned short, bzt::make_unsigned_t<volatile EnumWithUnderlyingShort>>);
    static_assert(bzt::is_same_v<volatile unsigned short, bzt::make_unsigned_t<volatile EnumWithUnderlyingUShort>>);
    static_assert(bzt::is_same_v<volatile unsigned int, bzt::make_unsigned_t<volatile EnumWithUnderlyingInt>>);
    static_assert(bzt::is_same_v<volatile unsigned int, bzt::make_unsigned_t<volatile EnumWithUnderlyingUInt>>);
    static_assert(bzt::is_same_v<volatile unsigned long, bzt::make_unsigned_t<volatile EnumWithUnderlyingLong>>);
    static_assert(bzt::is_same_v<volatile unsigned long, bzt::make_unsigned_t<volatile EnumWithUnderlyingULong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            volatile unsigned long, volatile unsigned long long>,
            bzt::make_unsigned_t<volatile EnumWithUnderlyingLongLong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            volatile unsigned long, volatile unsigned long long>,
            bzt::make_unsigned_t<volatile EnumWithUnderlyingULongLong>>);

    static_assert(bzt::is_same_v<const volatile unsigned char, bzt::make_unsigned_t<const volatile EnumWithUnderlyingChar>>);
    static_assert(bzt::is_same_v<const volatile unsigned char, bzt::make_unsigned_t<const volatile EnumWithUnderlyingUChar>>);
    static_assert(bzt::is_same_v<const volatile unsigned short, bzt::make_unsigned_t<const volatile EnumWithUnderlyingShort>>);
    static_assert(bzt::is_same_v<const volatile unsigned short, bzt::make_unsigned_t<const volatile EnumWithUnderlyingUShort>>);
    static_assert(bzt::is_same_v<const volatile unsigned int, bzt::make_unsigned_t<const volatile EnumWithUnderlyingInt>>);
    static_assert(bzt::is_same_v<const volatile unsigned int, bzt::make_unsigned_t<const volatile EnumWithUnderlyingUInt>>);
    static_assert(bzt::is_same_v<const volatile unsigned long, bzt::make_unsigned_t<const volatile EnumWithUnderlyingLong>>);
    static_assert(bzt::is_same_v<const volatile unsigned long, bzt::make_unsigned_t<const volatile EnumWithUnderlyingULong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            const volatile unsigned long, const volatile unsigned long long>,
            bzt::make_unsigned_t<const volatile EnumWithUnderlyingLongLong>>);
    static_assert(bzt::is_same_v<std::conditional_t<sizeof(long) == sizeof(long long),
            const volatile unsigned long, const volatile unsigned long long>,
            bzt::make_unsigned_t<const volatile EnumWithUnderlyingULongLong>>);

#if __cplusplus > 201703L
    static_assert(sizeof(bzt::make_unsigned_t<char8_t>) == 1);
    static_assert(sizeof(bzt::make_unsigned_t<const char8_t>) == 1);
    static_assert(sizeof(bzt::make_unsigned_t<volatile char8_t>) == 1);
    static_assert(sizeof(bzt::make_unsigned_t<const volatile char8_t>) == 1);
#endif
    static_assert(sizeof(bzt::make_unsigned_t<char16_t>) == 2);
    static_assert(sizeof(bzt::make_unsigned_t<const char16_t>) == 2);
    static_assert(sizeof(bzt::make_unsigned_t<volatile char16_t>) == 2);
    static_assert(sizeof(bzt::make_unsigned_t<const volatile char16_t>) == 2);
    static_assert(sizeof(bzt::make_unsigned_t<char32_t>) == 4);
    static_assert(sizeof(bzt::make_unsigned_t<const char32_t>) == 4);
    static_assert(sizeof(bzt::make_unsigned_t<volatile char32_t>) == 4);
    static_assert(sizeof(bzt::make_unsigned_t<const volatile char32_t>) == 4);
    static_assert(sizeof(bzt::make_unsigned_t<wchar_t>) == 2 ||
                  sizeof(bzt::make_unsigned_t<wchar_t>) == 4);
    static_assert(sizeof(bzt::make_unsigned_t<const wchar_t>) == 2 ||
                  sizeof(bzt::make_unsigned_t<const wchar_t>) == 4);
    static_assert(sizeof(bzt::make_unsigned_t<volatile wchar_t>) == 2 ||
                  sizeof(bzt::make_unsigned_t<volatile wchar_t>) == 4);
    static_assert(sizeof(bzt::make_unsigned_t<const volatile wchar_t>) == 2 ||
                  sizeof(bzt::make_unsigned_t<const volatile wchar_t>) == 4);
}

[[maybe_unused]] void test_is_constructible(){
    static_assert(bzt::is_constructible_v<Constructible, int>);
    static_assert(bzt::is_constructible_v<Constructible, float>);
    static_assert(bzt::is_constructible_v<Constructible, int, std::size_t>);
    static_assert(bzt::is_constructible_v<Constructible, EnumClassType>);
    static_assert(bzt::is_constructible_v<Constructible, EmptyClassType>);
    static_assert(bzt::is_constructible_v<Constructible, EmptyClassType, Tp, UnionTypeWithClassMember>);
    static_assert(!bzt::is_constructible_v<Constructible, double>);
    static_assert(!bzt::is_constructible_v<Constructible, EmptyStructType>);
    static_assert(!bzt::is_constructible_v<Constructible, StructTypeWithEnumMember>);
}

[[maybe_unused]] void test_is_default_constructible() {
    static_assert(!bzt::is_default_constructible_v<Constructible>);
    static_assert(bzt::is_default_constructible_v<int>);
    static_assert(bzt::is_default_constructible_v<unsigned int>);
    static_assert(bzt::is_default_constructible_v<long>);
    static_assert(bzt::is_default_constructible_v<EmptyClassType>);
    static_assert(bzt::is_default_constructible_v<Tp>);
}

[[maybe_unused]] void test_is_copy_constructible() {
    static_assert(bzt::is_copy_constructible_v<int>);
    static_assert(bzt::is_copy_constructible_v<long>);
    static_assert(bzt::is_copy_constructible_v<EnumType>);
    static_assert(bzt::is_copy_constructible_v<StructTypeWithEnumMember>);
    static_assert(bzt::is_copy_constructible_v<UnionType>);
    static_assert(bzt::is_copy_constructible_v<ImplicitConstructibleClass>);
    static_assert(bzt::is_copy_constructible_v<ExplicitCopyConstructibleClass>);
    static_assert(!bzt::is_copy_constructible_v<NonCopyConstructibleClass>);
    static_assert(bzt::is_copy_constructible_v<ImplicitCopyConstructibleStruct>);
    static_assert(bzt::is_copy_constructible_v<ExplicitCopyConstructibleStruct>);
    static_assert(!bzt::is_copy_constructible_v<NonCopyConstructibleStruct>);
}

[[maybe_unused]] void test_is_move_constructible() {
    static_assert(bzt::is_move_constructible_v<int>);
    static_assert(bzt::is_move_constructible_v<long>);
    static_assert(bzt::is_move_constructible_v<EnumType>);
    static_assert(bzt::is_move_constructible_v<StructTypeWithEnumMember>);
    static_assert(bzt::is_move_constructible_v<UnionType>);
    static_assert(bzt::is_move_constructible_v<ImplicitMoveConstructibleClass>);
    static_assert(bzt::is_move_constructible_v<ExplicitMoveConstructibleClass>);
    static_assert(!bzt::is_move_constructible_v<NonMoveConstructibleClass>);
    static_assert(bzt::is_move_constructible_v<ImplicitMoveConstructibleStruct>);
    static_assert(bzt::is_move_constructible_v<ExplicitMoveConstructibleStruct>);
    static_assert(!bzt::is_move_constructible_v<NonMoveConstructibleStruct>);
}

[[maybe_unused]] void test_is_assignable() {
    static_assert(!bzt::is_assignable_v<int,int>);
    static_assert(bzt::is_assignable_v<int&,int>);
    static_assert(!bzt::is_assignable_v<int,double>);
    static_assert(bzt::is_assignable_v<AssignableFromIntClass&, AssignableFromIntClass>);
    static_assert(bzt::is_assignable_v<AssignableFromIntClass&, AssignableFromIntClass&&>);
    static_assert(bzt::is_assignable_v<AssignableFromIntClass&, int>);
    static_assert(bzt::is_assignable_v<AssignableFromIntClass&, const int>);
    static_assert(bzt::is_assignable_v<AssignableFromIntClass&, const int &>);
    static_assert(!bzt::is_assignable_v<NonAssignableClass&, NonAssignableClass>);
    static_assert(!bzt::is_assignable_v<NonAssignableClass&, NonAssignableClass&&>);
    static_assert(!bzt::is_assignable_v<NonAssignableClass&, int>);
    static_assert(!bzt::is_assignable_v<NonAssignableClass&, const int>);
    static_assert(!bzt::is_assignable_v<NonAssignableClass&, const int &>);
}

[[maybe_unused]] void test_is_copy_assignable() {
    static_assert(bzt::is_copy_assignable_v<AssignableFromIntClass>);
    static_assert(!bzt::is_copy_assignable_v<NonAssignableClass>);
    static_assert(bzt::is_copy_assignable_v<int>);
    static_assert(bzt::is_copy_assignable_v<float>);
    static_assert(bzt::is_copy_assignable_v<void*>);
    static_assert(bzt::is_copy_assignable_v<bzt::nullptr_t>);
    static_assert(bzt::is_copy_assignable_v<EnumType>);
    static_assert(bzt::is_copy_assignable_v<EnumClassType>);
}

[[maybe_unused]] void test_is_move_assignable() {
    static_assert(bzt::is_move_assignable_v<AssignableFromIntClass>);
    static_assert(!bzt::is_move_assignable_v<NonAssignableClass>);
    static_assert(bzt::is_move_assignable_v<int>);
    static_assert(bzt::is_move_assignable_v<float>);
    static_assert(bzt::is_move_assignable_v<void*>);
    static_assert(bzt::is_move_assignable_v<bzt::nullptr_t>);
    static_assert(bzt::is_move_assignable_v<EnumType>);
    static_assert(bzt::is_move_assignable_v<EnumClassType>);
}

[[maybe_unused]] void test_is_swappable_with() {
    static_assert(bzt::is_swappable_with_v<int&, int&>);
    static_assert(bzt::is_swappable_with_v<float&, float&>);
    static_assert(bzt::is_swappable_with_v<char&, char&>);
    static_assert(bzt::is_swappable_with_v<double&, double&>);
    static_assert(bzt::is_swappable_with_v<signed long&, signed long&>);
    static_assert(bzt::is_swappable_with_v<unsigned short&, unsigned short&>);
    static_assert(bzt::is_swappable_with_v<Tp&, Tp&>);
    static_assert(bzt::is_swappable_with_v<UnionType&, UnionType&>);
    static_assert(bzt::is_swappable_with_v<EnumWithUnderlyingChar&, EnumWithUnderlyingChar&>);
    static_assert(bzt::is_swappable_with_v<EnumWithUnderlyingShort&, EnumWithUnderlyingShort&>);
    static_assert(bzt::is_swappable_with_v<EnumWithUnderlyingInt&, EnumWithUnderlyingInt&>);
    static_assert(bzt::is_swappable_with_v<EnumWithUnderlyingLong&, EnumWithUnderlyingLong&>);
    static_assert(bzt::is_swappable_with_v<EnumWithUnderlyingLongLong&, EnumWithUnderlyingLongLong&>);
    static_assert(bzt::is_swappable_with_v<EnumWithUnderlyingUChar&, EnumWithUnderlyingUChar&>);
    static_assert(bzt::is_swappable_with_v<EnumWithUnderlyingUShort&, EnumWithUnderlyingUShort&>);
    static_assert(bzt::is_swappable_with_v<EnumWithUnderlyingUInt&, EnumWithUnderlyingUInt&>);
    static_assert(bzt::is_swappable_with_v<EnumWithUnderlyingULong&, EnumWithUnderlyingULong&>);
    static_assert(bzt::is_swappable_with_v<EnumWithUnderlyingULongLong&, EnumWithUnderlyingULongLong&>);
}

[[maybe_unused]] void test_is_swappable() {
    static_assert(bzt::is_swappable_v<int>);
    static_assert(bzt::is_swappable_v<float>);
    static_assert(bzt::is_swappable_v<char>);
    static_assert(bzt::is_swappable_v<double>);
    static_assert(bzt::is_swappable_v<signed long>);
    static_assert(bzt::is_swappable_v<unsigned short>);
    static_assert(bzt::is_swappable_v<Tp>);
    static_assert(bzt::is_swappable_v<UnionType>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingChar>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingShort>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingInt>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingLong>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingLongLong>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingUChar>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingUShort>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingUInt>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingULong>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingULongLong>);
}

[[maybe_unused]] void test_is_destructible() {
    static_assert(bzt::is_destructible_v<int>);
    static_assert(bzt::is_destructible_v<float>);
    static_assert(bzt::is_destructible_v<char>);
    static_assert(bzt::is_destructible_v<double>);
    static_assert(bzt::is_destructible_v<signed long>);
    static_assert(bzt::is_destructible_v<unsigned short>);
    static_assert(bzt::is_destructible_v<Tp>);
    static_assert(bzt::is_destructible_v<UnionType>);
    static_assert(bzt::is_destructible_v<EnumWithUnderlyingChar>);
    static_assert(bzt::is_destructible_v<EnumWithUnderlyingShort>);
    static_assert(bzt::is_destructible_v<EnumWithUnderlyingInt>);
    static_assert(bzt::is_destructible_v<EnumWithUnderlyingLong>);
    static_assert(bzt::is_destructible_v<EnumWithUnderlyingLongLong>);
    static_assert(bzt::is_destructible_v<EnumWithUnderlyingUChar>);
    static_assert(bzt::is_destructible_v<EnumWithUnderlyingUShort>);
    static_assert(bzt::is_destructible_v<EnumWithUnderlyingUInt>);
    static_assert(bzt::is_destructible_v<EnumWithUnderlyingULong>);
    static_assert(bzt::is_destructible_v<EnumWithUnderlyingULongLong>);
    static_assert(bzt::is_destructible_v<DefaultDestructibleClass>);
    static_assert(!bzt::is_destructible_v<NonDestructibleClass>);
}

[[maybe_unused]] void test_is_trivially_constructible() {
    static_assert(!bzt::is_trivially_constructible_v<Constructible, float>);
    static_assert(!bzt::is_trivially_constructible_v<Constructible, int, std::size_t>);
    static_assert(!bzt::is_trivially_constructible_v<Constructible, EnumClassType>);
    static_assert(!bzt::is_trivially_constructible_v<Constructible, EmptyClassType>);
    static_assert(!bzt::is_trivially_constructible_v<Constructible, EmptyClassType, Tp, UnionTypeWithClassMember>);
    static_assert(bzt::is_trivially_constructible_v<Constructible, const Constructible&>);
    static_assert(bzt::is_constructible_v<Constructible, Constructible&&>);
}

[[maybe_unused]] void test_is_trivially_default_constructible() {
    static_assert(!bzt::is_trivially_default_constructible_v<Constructible>);
    static_assert(!bzt::is_trivially_default_constructible_v<DeletedConstructors>);
    static_assert(bzt::is_trivially_default_constructible_v<unsigned int>);
    static_assert(bzt::is_trivially_default_constructible_v<long>);
    static_assert(bzt::is_trivially_default_constructible_v<EnumClassType>);
    static_assert(bzt::is_trivially_default_constructible_v<EmptyClassType>);
}

[[maybe_unused]] void test_is_trivially_copy_constructible() {
    static_assert(bzt::is_trivially_copy_constructible_v<int>);
    static_assert(bzt::is_trivially_copy_constructible_v<long>);
    static_assert(bzt::is_trivially_copy_constructible_v<EnumType>);
    static_assert(bzt::is_trivially_copy_constructible_v<StructTypeWithEnumMember>);
    static_assert(bzt::is_trivially_copy_constructible_v<UnionType>);
    static_assert(bzt::is_trivially_copy_constructible_v<ImplicitConstructibleClass>);
    static_assert(bzt::is_trivially_copy_constructible_v<ExplicitCopyConstructibleClass>);
    static_assert(!bzt::is_trivially_copy_constructible_v<NonCopyConstructibleClass>);
    static_assert(bzt::is_trivially_copy_constructible_v<ImplicitCopyConstructibleStruct>);
    static_assert(bzt::is_trivially_copy_constructible_v<ExplicitCopyConstructibleStruct>);
    static_assert(!bzt::is_trivially_copy_constructible_v<NonCopyConstructibleStruct>);
    static_assert(!bzt::is_trivially_copy_constructible_v<DeletedConstructors>);
}

[[maybe_unused]] void test_is_trivially_move_constructible() {
    static_assert(bzt::is_trivially_move_constructible_v<int>);
    static_assert(bzt::is_trivially_move_constructible_v<long>);
    static_assert(bzt::is_trivially_move_constructible_v<EnumType>);
    static_assert(bzt::is_trivially_move_constructible_v<StructTypeWithEnumMember>);
    static_assert(bzt::is_trivially_move_constructible_v<UnionType>);
    static_assert(bzt::is_trivially_move_constructible_v<ImplicitMoveConstructibleClass>);
    static_assert(bzt::is_trivially_move_constructible_v<ExplicitMoveConstructibleClass>);
    static_assert(!bzt::is_trivially_move_constructible_v<NonMoveConstructibleClass>);
    static_assert(bzt::is_trivially_move_constructible_v<ImplicitMoveConstructibleStruct>);
    static_assert(bzt::is_trivially_move_constructible_v<ExplicitMoveConstructibleStruct>);
    static_assert(!bzt::is_trivially_move_constructible_v<NonMoveConstructibleStruct>);
    static_assert(!bzt::is_trivially_move_constructible_v<DeletedConstructors>);
}

[[maybe_unused]] void test_is_trivially_assignable() {
    static_assert(!bzt::is_trivially_assignable_v<int,int>);
    static_assert(bzt::is_trivially_assignable_v<int&,int>);
    static_assert(!bzt::is_trivially_assignable_v<int,double>);
    static_assert(bzt::is_trivially_assignable_v<AssignableFromIntClass&, AssignableFromIntClass>);
    static_assert(bzt::is_trivially_assignable_v<AssignableFromIntClass&, AssignableFromIntClass&&>);
    static_assert(bzt::is_trivially_assignable_v<TriviallyAssignable&, TriviallyAssignable>);
    static_assert(bzt::is_trivially_assignable_v<TriviallyAssignable&, TriviallyAssignable&&>);
    static_assert(!bzt::is_trivially_assignable_v<NonAssignableClass&, NonAssignableClass>);
    static_assert(!bzt::is_trivially_assignable_v<NonAssignableClass&, NonAssignableClass&&>);
    static_assert(!bzt::is_trivially_assignable_v<NonAssignableClass&, int>);
    static_assert(!bzt::is_trivially_assignable_v<NonAssignableClass&, const int>);
    static_assert(!bzt::is_trivially_assignable_v<NonAssignableClass&, const int &>);
    static_assert(!bzt::is_trivially_assignable_v<NonTriviallyAssignable&, const NonTriviallyAssignable&>);
    static_assert(!bzt::is_trivially_assignable_v<NonTriviallyAssignable&, const NonTriviallyAssignable>);
    static_assert(!bzt::is_trivially_assignable_v<NonTriviallyAssignable&, NonTriviallyAssignable>);
    static_assert(!bzt::is_trivially_assignable_v<NonAssignableClass&, NonTriviallyAssignable&&>);
}

[[maybe_unused]] void test_is_trivially_copy_assignable() {
    static_assert(bzt::is_trivially_copy_assignable_v<int>);
    static_assert(bzt::is_trivially_copy_assignable_v<long>);
    static_assert(bzt::is_trivially_copy_assignable_v<EnumType>);
    static_assert(bzt::is_trivially_copy_assignable_v<StructTypeWithEnumMember>);
    static_assert(bzt::is_trivially_copy_assignable_v<UnionType>);
    static_assert(bzt::is_trivially_copy_assignable_v<TriviallyAssignable>);
    static_assert(!bzt::is_trivially_copy_assignable_v<NonTriviallyAssignable>);
    static_assert(!bzt::is_trivially_copy_assignable_v<NonAssignableClass>);
}

[[maybe_unused]] void test_is_trivially_move_assignable() {
    static_assert(bzt::is_trivially_move_assignable_v<AssignableFromIntClass>);
    static_assert(!bzt::is_trivially_move_assignable_v<NonAssignableClass>);
    static_assert(bzt::is_trivially_move_assignable_v<int>);
    static_assert(bzt::is_trivially_move_assignable_v<float>);
    static_assert(bzt::is_trivially_move_assignable_v<void*>);
    static_assert(bzt::is_trivially_move_assignable_v<bzt::nullptr_t>);
    static_assert(bzt::is_trivially_move_assignable_v<EnumType>);
    static_assert(bzt::is_trivially_move_assignable_v<EnumClassType>);
    static_assert(!bzt::is_trivially_move_assignable_v<NonTriviallyAssignable>);
    static_assert(!bzt::is_trivially_move_assignable_v<NonAssignableClass>);
    static_assert(bzt::is_trivially_move_assignable_v<TriviallyAssignable>);
}

[[maybe_unused]] void test_is_trivially_destructible() {
    static_assert(bzt::is_trivially_destructible_v<int>);
    static_assert(bzt::is_trivially_destructible_v<float>);
    static_assert(bzt::is_trivially_destructible_v<char>);
    static_assert(bzt::is_trivially_destructible_v<double>);
    static_assert(bzt::is_trivially_destructible_v<signed long>);
    static_assert(bzt::is_trivially_destructible_v<unsigned short>);
    static_assert(bzt::is_trivially_destructible_v<EmptyClassType>);
    static_assert(bzt::is_trivially_destructible_v<UnionType>);
    static_assert(bzt::is_trivially_destructible_v<EnumWithUnderlyingChar>);
    static_assert(bzt::is_trivially_destructible_v<EnumWithUnderlyingShort>);
    static_assert(bzt::is_trivially_destructible_v<EnumWithUnderlyingInt>);
    static_assert(bzt::is_trivially_destructible_v<EnumWithUnderlyingLong>);
    static_assert(bzt::is_trivially_destructible_v<EnumWithUnderlyingLongLong>);
    static_assert(bzt::is_trivially_destructible_v<EnumWithUnderlyingUChar>);
    static_assert(bzt::is_trivially_destructible_v<EnumWithUnderlyingUShort>);
    static_assert(bzt::is_trivially_destructible_v<EnumWithUnderlyingUInt>);
    static_assert(bzt::is_trivially_destructible_v<EnumWithUnderlyingULong>);
    static_assert(bzt::is_trivially_destructible_v<EnumWithUnderlyingULongLong>);
    static_assert(bzt::is_trivially_destructible_v<DefaultDestructibleClass>);
    static_assert(!bzt::is_trivially_destructible_v<NonDestructibleClass>);
    static_assert(!bzt::is_trivially_destructible_v<NonTriviallyDestructibleClass>);
}

[[maybe_unused]] void test_is_trivially_copyable() {
    static_assert(bzt::is_trivially_copyable_v<int>);
    static_assert(bzt::is_trivially_copyable_v<long>);
    static_assert(bzt::is_trivially_copyable_v<EnumType>);
    static_assert(bzt::is_trivially_copyable_v<StructTypeWithEnumMember>);
    static_assert(bzt::is_trivially_copyable_v<UnionType>);
    static_assert(bzt::is_trivially_copyable_v<ImplicitConstructibleClass>);
    static_assert(bzt::is_trivially_copyable_v<ExplicitCopyConstructibleClass>);
    static_assert(bzt::is_trivially_copyable_v<ImplicitCopyConstructibleStruct>);
    static_assert(bzt::is_trivially_copyable_v<ExplicitCopyConstructibleStruct>);
    static_assert(bzt::is_trivially_copyable_v<NonCopyConstructibleClass>);
    static_assert(bzt::is_trivially_copyable_v<NonCopyConstructibleStruct>);
    static_assert(bzt::is_trivially_copyable_v<DeletedConstructors>);
    static_assert(!bzt::is_trivially_copyable_v<NonTriviallyCopyableClass_1>);
    static_assert(!bzt::is_trivially_copyable_v<NonTriviallyCopyableClass_2>);
    static_assert(!bzt::is_trivially_copyable_v<NonTriviallyCopyableClass_3>);
    static_assert(!bzt::is_trivially_copyable_v<NonTriviallyCopyableClass_4>);
}

[[maybe_unused]] void test_is_trivial()
{
    static_assert(bzt::is_trivial_v<int>);
    static_assert(bzt::is_trivial_v<float>);
    static_assert(bzt::is_trivial_v<char>);
    static_assert(bzt::is_trivial_v<double>);
    static_assert(bzt::is_trivial_v<signed long>);
    static_assert(bzt::is_trivial_v<unsigned short>);
    static_assert(bzt::is_trivial_v<EmptyClassType>);
    static_assert(bzt::is_trivial_v<UnionType>);
    static_assert(bzt::is_trivial_v<EnumWithUnderlyingChar>);
    static_assert(bzt::is_trivial_v<EnumWithUnderlyingShort>);
    static_assert(bzt::is_trivial_v<EnumWithUnderlyingInt>);
    static_assert(bzt::is_trivial_v<EnumWithUnderlyingLong>);
    static_assert(bzt::is_trivial_v<EnumWithUnderlyingLongLong>);
    static_assert(bzt::is_trivial_v<EnumWithUnderlyingUChar>);
    static_assert(bzt::is_trivial_v<EnumWithUnderlyingUShort>);
    static_assert(bzt::is_trivial_v<EnumWithUnderlyingUInt>);
    static_assert(bzt::is_trivial_v<EnumWithUnderlyingULong>);
    static_assert(bzt::is_trivial_v<EnumWithUnderlyingULongLong>);
    static_assert(bzt::is_trivial_v<DefaultDestructibleClass>);
    static_assert(bzt::is_trivial_v<EmptyClassType[]>);
    static_assert(bzt::is_trivial_v<EmptyClassType[55]>);
    static_assert(!bzt::is_trivial_v<NonTriviallyCopyableClass_1>);
    static_assert(!bzt::is_trivial_v<NonTriviallyCopyableClass_2>);
    static_assert(!bzt::is_trivial_v<NonTriviallyCopyableClass_3>);
    static_assert(!bzt::is_trivial_v<NonTriviallyCopyableClass_4>);
    static_assert(!bzt::is_trivial_v<NonTriviallyCopyableClass_1[]>);
    static_assert(!bzt::is_trivial_v<NonTriviallyCopyableClass_2[]>);
    static_assert(!bzt::is_trivial_v<NonTriviallyCopyableClass_3[]>);
    static_assert(!bzt::is_trivial_v<NonTriviallyCopyableClass_4[]>);
    static_assert(!bzt::is_trivial_v<const NonTriviallyCopyableClass_1[]>);
    static_assert(!bzt::is_trivial_v<volatile NonTriviallyCopyableClass_2[]>);
    static_assert(!bzt::is_trivial_v<const volatile NonTriviallyCopyableClass_3[]>);
    static_assert(bzt::is_trivial_v<ImplicitConstructibleClass>);
    static_assert(bzt::is_trivial_v<ExplicitDefaultConstructors>);
    static_assert(bzt::is_trivial_v<ExplicitDefaultConstructors[]>);
}

[[maybe_unused]] void test_is_standard_layout()
{
    static_assert(bzt::is_standard_layout_v<int>);
    static_assert(bzt::is_standard_layout_v<float>);
    static_assert(bzt::is_standard_layout_v<char>);
    static_assert(bzt::is_standard_layout_v<double>);
    static_assert(bzt::is_standard_layout_v<signed long>);
    static_assert(bzt::is_standard_layout_v<unsigned short>);
    static_assert(bzt::is_standard_layout_v<EmptyClassType>);
    static_assert(bzt::is_standard_layout_v<UnionType>);
    static_assert(bzt::is_standard_layout_v<EnumWithUnderlyingChar>);
    static_assert(bzt::is_standard_layout_v<EnumWithUnderlyingShort>);
    static_assert(bzt::is_standard_layout_v<EnumWithUnderlyingInt>);
    static_assert(bzt::is_standard_layout_v<EnumWithUnderlyingLong>);
    static_assert(bzt::is_standard_layout_v<EnumWithUnderlyingLongLong>);
    static_assert(bzt::is_standard_layout_v<EnumWithUnderlyingUChar>);
    static_assert(bzt::is_standard_layout_v<EnumWithUnderlyingUShort>);
    static_assert(bzt::is_standard_layout_v<EnumWithUnderlyingUInt>);
    static_assert(bzt::is_standard_layout_v<EnumWithUnderlyingULong>);
    static_assert(bzt::is_standard_layout_v<EnumWithUnderlyingULongLong>);
    static_assert(!bzt::is_standard_layout_v<VirtualClass>);
    static_assert(!bzt::is_standard_layout_v<VirtualPureClass>);
    static_assert(!bzt::is_standard_layout_v<ClassWithDifferentAccessControl>);
    static_assert(!bzt::is_standard_layout_v<ClassWithReferenceMemberType>);
    // Fail with std as well using GCC compiler
    // static_assert(!bzt::is_standard_layout_v<HasTwoBaseClassSubObjects>);
}

[[maybe_unused]] void test_is_empty()
{
    static_assert(bzt::is_empty_v<EmptyClassType>);
    static_assert(bzt::is_empty_v<EmptyStructType>);
    static_assert(!bzt::is_empty_v<EnumClassType>);
    static_assert(!bzt::is_empty_v<EnumType>);
    static_assert(!bzt::is_empty_v<UnionType>);
    static_assert(!bzt::is_empty_v<VirtualClass>);
    static_assert(!std::is_empty_v<VirtualPureClass>);
    static_assert(!std::is_empty_v<ClassWithReferenceMemberType>);
}

[[maybe_unused]] void test_is_polymorphic()
{
    static_assert(bzt::is_polymorphic_v<VirtualClass>);
    static_assert(std::is_polymorphic_v<VirtualPureClass>);
    static_assert(bzt::is_polymorphic_v<DerivedFromVirtualClass>);
    static_assert(bzt::is_polymorphic_v<VirtualDestructorClass>);
}

[[maybe_unused]] void test_is_abstract()
{
    static_assert(!bzt::is_abstract_v<VirtualClass>);
    static_assert(std::is_abstract_v<VirtualPureClass>);
    static_assert(!bzt::is_abstract_v<DerivedFromVirtualClass>);
    static_assert(bzt::is_abstract_v<DerivedFromVirtualPureClass>);
}

[[maybe_unused]] void test_is_final()
{
    static_assert(bzt::is_final_v<finalClass>);
    static_assert(bzt::is_final_v<finalStruct>);
    static_assert(!bzt::is_final_v<EmptyClassType>);
    static_assert(!bzt::is_final_v<EmptyStructType>);
    static_assert(!bzt::is_abstract_v<DerivedFromVirtualClass>);
    static_assert(bzt::is_abstract_v<DerivedFromVirtualPureClass>);
}

[[maybe_unused]] void test_is_aggregate()
{
    static_assert(bzt::is_aggregate_v<Tp[]>);
    static_assert(bzt::is_aggregate_v<EmptyClassType>);
    static_assert(!bzt::is_aggregate_v<VirtualClass>);
    static_assert(!bzt::is_aggregate_v<VirtualPureClass>);
    static_assert(!bzt::is_aggregate_v<DerivedFromVirtualClass>);
    static_assert(!bzt::is_aggregate_v<DerivedFromVirtualPureClass>);
    static_assert(!bzt::is_aggregate_v<DefaultMemberInitializationClass>);
    static_assert(!bzt::is_aggregate_v<PrivateInheritedBaseClass>);
    static_assert(!bzt::is_aggregate_v<ProtectedInheritedBaseClass>);
    static_assert(!bzt::is_aggregate_v<ClassWithReferenceMemberType>);
    static_assert(!bzt::is_aggregate_v<Constructible>);
    static_assert(!bzt::is_aggregate_v<PrivateMemberClass>);
    static_assert(!bzt::is_aggregate_v<ProtectedMemberClass>);
}

[[maybe_unused]] void test_is_nothrow_constructible()
{
    static_assert(!bzt::is_nothrow_constructible_v<Constructible, float>);
    static_assert(!bzt::is_nothrow_constructible_v<Constructible, int, std::size_t>);
    static_assert(!bzt::is_nothrow_constructible_v<Constructible, EnumClassType>);
    static_assert(!bzt::is_nothrow_constructible_v<Constructible, EmptyClassType>);
    static_assert(!bzt::is_nothrow_constructible_v<Constructible, EmptyClassType, Tp, UnionTypeWithClassMember>);
    static_assert(bzt::is_nothrow_constructible_v<NoThrowConstructible, float>);
    static_assert(bzt::is_nothrow_constructible_v<NoThrowConstructible, int, std::size_t>);
    static_assert(bzt::is_nothrow_constructible_v<NoThrowConstructible, EnumClassType>);
    static_assert(bzt::is_nothrow_constructible_v<NoThrowConstructible, EmptyClassType>);
    static_assert(bzt::is_nothrow_constructible_v<NoThrowConstructible, EmptyClassType, Tp, UnionTypeWithClassMember>);
}

[[maybe_unused]] void test_is_nothrow_default_constructible()
{
    static_assert(!bzt::is_nothrow_default_constructible_v<Constructible>);
    static_assert(!bzt::is_nothrow_default_constructible_v<NoThrowConstructible>);
    static_assert(!bzt::is_nothrow_default_constructible_v<DeletedConstructors>);
    static_assert(bzt::is_nothrow_default_constructible_v<ExplicitNoThrowConstructors>);
    static_assert(!bzt::is_nothrow_default_constructible_v<ExplicitThrowConstructors>);
    static_assert(bzt::is_nothrow_default_constructible_v<unsigned int>);
    static_assert(bzt::is_nothrow_default_constructible_v<long>);
    static_assert(bzt::is_nothrow_default_constructible_v<EnumClassType>);
    static_assert(bzt::is_nothrow_default_constructible_v<EmptyClassType>);
}

[[maybe_unused]] void test_is_nothrow_copy_constructible()
{
    static_assert(bzt::is_nothrow_copy_constructible_v<int>);
    static_assert(bzt::is_nothrow_copy_constructible_v<long>);
    static_assert(bzt::is_nothrow_copy_constructible_v<EnumType>);
    static_assert(bzt::is_nothrow_copy_constructible_v<StructTypeWithEnumMember>);
    static_assert(bzt::is_nothrow_copy_constructible_v<UnionType>);
    static_assert(bzt::is_nothrow_copy_constructible_v<ExplicitNoThrowConstructors>);
    static_assert(!bzt::is_nothrow_copy_constructible_v<ExplicitThrowConstructors>);
    static_assert(bzt::is_nothrow_copy_constructible_v<ImplicitConstructibleClass>);
    static_assert(bzt::is_nothrow_copy_constructible_v<ExplicitCopyConstructibleClass>);
    static_assert(!bzt::is_nothrow_copy_constructible_v<NonCopyConstructibleClass>);
    static_assert(bzt::is_nothrow_copy_constructible_v<ImplicitCopyConstructibleStruct>);
    static_assert(bzt::is_nothrow_copy_constructible_v<ExplicitCopyConstructibleStruct>);
    static_assert(!bzt::is_nothrow_copy_constructible_v<NonCopyConstructibleStruct>);
    static_assert(!bzt::is_nothrow_copy_constructible_v<DeletedConstructors>);
}

[[maybe_unused]] void test_is_nothrow_move_constructible()
{
    static_assert(bzt::is_nothrow_move_constructible_v<int>);
    static_assert(bzt::is_nothrow_move_constructible_v<float>);
    static_assert(bzt::is_nothrow_move_constructible_v<void*>);
    static_assert(bzt::is_nothrow_move_constructible_v<bzt::nullptr_t>);
    static_assert(bzt::is_nothrow_move_constructible_v<EnumType>);
    static_assert(bzt::is_nothrow_move_constructible_v<EnumClassType>);
    static_assert(bzt::is_nothrow_move_constructible_v<ExplicitDefaultConstructors>);
    static_assert(!bzt::is_nothrow_move_constructible_v<DeletedConstructors>);
    static_assert(bzt::is_nothrow_move_constructible_v<ExplicitNoThrowConstructors>);
    static_assert(!bzt::is_nothrow_move_constructible_v<ExplicitThrowConstructors>);
    static_assert(!bzt::is_nothrow_move_constructible_v<ExplicitThrowConstructors>);
}

[[maybe_unused]] void test_is_nothrow_assignable()
{
    static_assert(!bzt::is_nothrow_assignable_v<int,int>);
    static_assert(bzt::is_nothrow_assignable_v<int&,int>);
    static_assert(!bzt::is_nothrow_assignable_v<int,double>);
    static_assert(bzt::is_nothrow_assignable_v<AssignableFromIntClass&, AssignableFromIntClass>);
    static_assert(bzt::is_nothrow_assignable_v<AssignableFromIntClass&, AssignableFromIntClass&&>);
    static_assert(bzt::is_nothrow_assignable_v<TriviallyAssignable&, TriviallyAssignable>);
    static_assert(bzt::is_nothrow_assignable_v<TriviallyAssignable&, TriviallyAssignable&&>);
    static_assert(!bzt::is_nothrow_assignable_v<NonAssignableClass&, NonAssignableClass>);
    static_assert(!bzt::is_nothrow_assignable_v<NonAssignableClass&, NonAssignableClass&&>);
    static_assert(!bzt::is_nothrow_assignable_v<NonAssignableClass&, int>);
    static_assert(!bzt::is_nothrow_assignable_v<NonAssignableClass&, const int>);
    static_assert(!bzt::is_nothrow_assignable_v<NonAssignableClass&, const int &>);
    static_assert(bzt::is_nothrow_assignable_v<NoThrowAssignable&, const NoThrowAssignable&>);
    static_assert(bzt::is_nothrow_assignable_v<NoThrowAssignable&, const NoThrowAssignable>);
    static_assert(bzt::is_nothrow_assignable_v<NoThrowAssignable&, NoThrowAssignable>);
    static_assert(!bzt::is_nothrow_assignable_v<ThrowAssignable&, const ThrowAssignable&>);
    static_assert(!bzt::is_nothrow_assignable_v<ThrowAssignable&, const ThrowAssignable>);
    static_assert(!bzt::is_nothrow_assignable_v<ThrowAssignable&, ThrowAssignable>);
}

[[maybe_unused]] void test_is_nothrow_copy_assignable()
{
    static_assert(bzt::is_nothrow_copy_assignable_v<int>);
    static_assert(bzt::is_nothrow_copy_assignable_v<long>);
    static_assert(bzt::is_nothrow_copy_assignable_v<EnumType>);
    static_assert(bzt::is_nothrow_copy_assignable_v<StructTypeWithEnumMember>);
    static_assert(bzt::is_nothrow_copy_assignable_v<UnionType>);
    static_assert(bzt::is_nothrow_copy_assignable_v<NoThrowAssignable>);
    static_assert(!bzt::is_nothrow_copy_assignable_v<ThrowAssignable>);
    static_assert(!bzt::is_nothrow_copy_assignable_v<NonAssignableClass>);
}

[[maybe_unused]] void test_is_nothrow_move_assignable()
{
    static_assert(bzt::is_nothrow_move_assignable_v<AssignableFromIntClass>);
    static_assert(!bzt::is_nothrow_move_assignable_v<NonAssignableClass>);
    static_assert(bzt::is_nothrow_move_assignable_v<int>);
    static_assert(bzt::is_nothrow_move_assignable_v<float>);
    static_assert(bzt::is_nothrow_move_assignable_v<void*>);
    static_assert(bzt::is_nothrow_move_assignable_v<bzt::nullptr_t>);
    static_assert(bzt::is_nothrow_move_assignable_v<EnumType>);
    static_assert(bzt::is_nothrow_move_assignable_v<EnumClassType>);
    static_assert(!bzt::is_nothrow_move_assignable_v<ThrowAssignable>);
    static_assert(bzt::is_nothrow_move_assignable_v<NoThrowAssignable>);
    static_assert(!bzt::is_nothrow_move_assignable_v<NonAssignableClass>);
}

[[maybe_unused]] void test_is_nothrow_swappable_with() {
    static_assert(bzt::is_nothrow_swappable_with_v<int&, int&>);
    static_assert(bzt::is_nothrow_swappable_with_v<float&, float&>);
    static_assert(bzt::is_nothrow_swappable_with_v<char&, char&>);
    static_assert(bzt::is_nothrow_swappable_with_v<double&, double&>);
    static_assert(bzt::is_nothrow_swappable_with_v<signed long&, signed long&>);
    static_assert(bzt::is_nothrow_swappable_with_v<unsigned short&, unsigned short&>);
    static_assert(bzt::is_nothrow_swappable_with_v<Tp&, Tp&>);
    static_assert(bzt::is_nothrow_swappable_with_v<UnionType&, UnionType&>);
    static_assert(bzt::is_nothrow_swappable_with_v<EnumWithUnderlyingChar&, EnumWithUnderlyingChar&>);
    static_assert(bzt::is_nothrow_swappable_with_v<EnumWithUnderlyingShort&, EnumWithUnderlyingShort&>);
    static_assert(bzt::is_nothrow_swappable_with_v<EnumWithUnderlyingInt&, EnumWithUnderlyingInt&>);
    static_assert(bzt::is_nothrow_swappable_with_v<EnumWithUnderlyingLong&, EnumWithUnderlyingLong&>);
    static_assert(bzt::is_nothrow_swappable_with_v<EnumWithUnderlyingLongLong&, EnumWithUnderlyingLongLong&>);
    static_assert(bzt::is_nothrow_swappable_with_v<EnumWithUnderlyingUChar&, EnumWithUnderlyingUChar&>);
    static_assert(bzt::is_nothrow_swappable_with_v<EnumWithUnderlyingUShort&, EnumWithUnderlyingUShort&>);
    static_assert(bzt::is_nothrow_swappable_with_v<EnumWithUnderlyingUInt&, EnumWithUnderlyingUInt&>);
    static_assert(bzt::is_nothrow_swappable_with_v<EnumWithUnderlyingULong&, EnumWithUnderlyingULong&>);
    static_assert(bzt::is_nothrow_swappable_with_v<EnumWithUnderlyingULongLong&, EnumWithUnderlyingULongLong&>);
    static_assert(!bzt::is_nothrow_swappable_with_v<ThrowAssignable&, ThrowAssignable&>);
    static_assert(!bzt::is_nothrow_swappable_with_v<ExplicitThrowConstructors&, ExplicitThrowConstructors&>);
    static_assert(!bzt::is_nothrow_swappable_with_v<NoThrowAssignable&, NoThrowAssignable&>);
    static_assert(bzt::is_nothrow_swappable_with_v<NoThrowAssignableAndConstructible&, NoThrowAssignableAndConstructible&>);
}

[[maybe_unused]] void test_is_nothrow_swappable() {
    static_assert(bzt::is_swappable_v<int>);
    static_assert(bzt::is_swappable_v<float>);
    static_assert(bzt::is_swappable_v<char>);
    static_assert(bzt::is_swappable_v<double>);
    static_assert(bzt::is_swappable_v<signed long>);
    static_assert(bzt::is_swappable_v<unsigned short>);
    static_assert(bzt::is_swappable_v<Tp>);
    static_assert(bzt::is_swappable_v<UnionType>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingChar>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingShort>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingInt>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingLong>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingLongLong>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingUChar>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingUShort>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingUInt>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingULong>);
    static_assert(bzt::is_swappable_v<EnumWithUnderlyingULongLong>);
    static_assert(!bzt::is_swappable_v<ThrowAssignable>);
    static_assert(!bzt::is_swappable_v<ExplicitThrowConstructors>);
    static_assert(!bzt::is_swappable_v<NoThrowAssignable>);
    static_assert(bzt::is_swappable_v<NoThrowAssignableAndConstructible>);
}

[[maybe_unused]] void test_is_nothrow_destructible()
{
    static_assert(bzt::is_nothrow_destructible_v<int>);
    static_assert(bzt::is_nothrow_destructible_v<float>);
    static_assert(bzt::is_nothrow_destructible_v<char>);
    static_assert(bzt::is_nothrow_destructible_v<double>);
    static_assert(bzt::is_nothrow_destructible_v<signed long>);
    static_assert(bzt::is_nothrow_destructible_v<unsigned short>);
    static_assert(bzt::is_nothrow_destructible_v<Tp>);
    static_assert(bzt::is_nothrow_destructible_v<UnionType>);
    static_assert(bzt::is_nothrow_destructible_v<EnumWithUnderlyingChar>);
    static_assert(bzt::is_nothrow_destructible_v<EnumWithUnderlyingShort>);
    static_assert(bzt::is_nothrow_destructible_v<EnumWithUnderlyingInt>);
    static_assert(bzt::is_nothrow_destructible_v<EnumWithUnderlyingLong>);
    static_assert(bzt::is_nothrow_destructible_v<EnumWithUnderlyingLongLong>);
    static_assert(bzt::is_nothrow_destructible_v<EnumWithUnderlyingUChar>);
    static_assert(bzt::is_nothrow_destructible_v<EnumWithUnderlyingUShort>);
    static_assert(bzt::is_nothrow_destructible_v<EnumWithUnderlyingUInt>);
    static_assert(bzt::is_nothrow_destructible_v<EnumWithUnderlyingULong>);
    static_assert(bzt::is_nothrow_destructible_v<EnumWithUnderlyingULongLong>);
    static_assert(bzt::is_nothrow_destructible_v<DefaultDestructibleClass>);
    static_assert(!bzt::is_nothrow_destructible_v<NonDestructibleClass>);
    static_assert(!bzt::is_nothrow_destructible_v<ThrowDestructibleClass>);
    static_assert(bzt::is_nothrow_destructible_v<NoThrowDestructibleClass>);
}

[[maybe_unused]] void test_has_virtual_destructor()
{
    static_assert(!bzt::has_virtual_destructor_v<EmptyClassType>);
    static_assert(!bzt::has_virtual_destructor_v<DefaultDestructibleClass>);
    static_assert(!bzt::has_virtual_destructor_v<NonDestructibleClass>);
    static_assert(bzt::has_virtual_destructor_v<VirtualDestructorClass>);
}

[[maybe_unused]] void test_has_unique_object_representations()
{
    static_assert(bzt::has_unique_object_representations_v<char>);
    static_assert(bzt::has_unique_object_representations_v<unsigned char>);
    static_assert(bzt::has_unique_object_representations_v<int>);
    static_assert(bzt::has_unique_object_representations_v<unsigned int>);
    static_assert(bzt::has_unique_object_representations_v<UniqueObjectRepresentationStruct>);
    static_assert(!bzt::has_unique_object_representations_v<NonUniqueObjectRepresentationStruct>);
}

[[maybe_unused]] void test_is_base_of()
{
    class A {};
    class B : A {};
    class C : B {};
    class D {};
    static_assert(bzt::is_base_of_v<A, A>);
    static_assert(bzt::is_base_of_v<A, B>);
    static_assert(bzt::is_base_of_v<A, C>);
    static_assert(!bzt::is_base_of_v<A, D>);
    static_assert(!bzt::is_base_of_v<B, A>);
    static_assert(!bzt::is_base_of_v<int, int>);
}

[[maybe_unused]] void test_is_convertible()
{
    class A {};
    class B : public A {};
    class C {};
    class D { public: operator C() const { return c; }  C c; };

    static_assert(bzt::is_convertible_v<B*, A*>);
    static_assert(!bzt::is_convertible_v<A*, B*>);
    static_assert(bzt::is_convertible_v<D, C>);
    static_assert(!bzt::is_convertible_v<B*, C*>);
}

[[maybe_unused]] void test_is_nothrow_convertible()
{
    class A {};
    class B : public A {};
    class C {};
    class D { public: explicit operator C() const noexcept(false) { return c; }  C c; };

    static_assert(bzt::is_nothrow_convertible_v<B*, A*>);
    static_assert(!bzt::is_nothrow_convertible_v<A*, B*>);
    static_assert(!bzt::is_nothrow_convertible_v<D, C>);
    static_assert(!bzt::is_nothrow_convertible_v<B*, C*>);
}

[[maybe_unused]] void test_alignment_of()
{
    static_assert(std::alignment_of_v<char> == bzt::alignment_of_v<char>);
    static_assert(std::alignment_of_v<short> == bzt::alignment_of_v<short>);
    static_assert(std::alignment_of_v<int> == bzt::alignment_of_v<int>);
    static_assert(std::alignment_of_v<long> == bzt::alignment_of_v<long>);
    static_assert(std::alignment_of_v<long long> == bzt::alignment_of_v<long long>);
    static_assert(std::alignment_of_v<EmptyClassType> == bzt::alignment_of_v<EmptyClassType>);
    static_assert(std::alignment_of_v<EmptyStructType> == bzt::alignment_of_v<EmptyStructType>);
    static_assert(std::alignment_of_v<EnumWithUnderlyingChar> == bzt::alignment_of_v<EnumWithUnderlyingChar>);
    static_assert(std::alignment_of_v<EnumWithUnderlyingShort> == bzt::alignment_of_v<EnumWithUnderlyingShort>);
    static_assert(std::alignment_of_v<EnumWithUnderlyingInt> == bzt::alignment_of_v<EnumWithUnderlyingInt>);
    static_assert(std::alignment_of_v<EnumWithUnderlyingLong> == bzt::alignment_of_v<EnumWithUnderlyingLong>);
    static_assert(std::alignment_of_v<EnumWithUnderlyingLongLong> == bzt::alignment_of_v<EnumWithUnderlyingLongLong>);
}

[[maybe_unused]] void test_decay()
{
    static_assert(bzt::is_same_v<int, bzt::decay_t<int>>);
    static_assert(bzt::is_same_v<int, bzt::decay_t<int &>>);
    static_assert(bzt::is_same_v<int, bzt::decay_t<int &&>>);
    static_assert(bzt::is_same_v<int, bzt::decay_t<const int &>>);
    static_assert(bzt::is_same_v<int *, bzt::decay_t<int[]>>);
    static_assert(bzt::is_same_v<int *, bzt::decay_t<int[2]>>);
    static_assert(bzt::is_same_v<int (*)(int), bzt::decay_t<int(int)>>);
}

[[maybe_unused]] void test_remove_cvref()
{
    static_assert(bzt::is_same_v<int, bzt::remove_cvref_t<int>>);
    static_assert(bzt::is_same_v<int, bzt::remove_cvref_t<int&>>);
    static_assert(bzt::is_same_v<int, bzt::remove_cvref_t<int&&>>);
    static_assert(bzt::is_same_v<int, bzt::remove_cvref_t<const int&>>);
    static_assert(bzt::is_same_v<int[2], bzt::remove_cvref_t<const int[2]>>);
    static_assert(bzt::is_same_v<int[2], bzt::remove_cvref_t<const int(&)[2]>>);
    static_assert(bzt::is_same_v<int(int), bzt::remove_cvref_t<int(int)>>);
}

[[maybe_unused]] void test_underlying_type()
{
    static_assert(bzt::is_same_v<char, bzt::underlying_type_t<EnumWithUnderlyingChar>>);
    static_assert(bzt::is_same_v<short, bzt::underlying_type_t<EnumWithUnderlyingShort>>);
    static_assert(bzt::is_same_v<int, bzt::underlying_type_t<EnumWithUnderlyingInt>>);
    static_assert(bzt::is_same_v<long, bzt::underlying_type_t<EnumWithUnderlyingLong>>);
    static_assert(bzt::is_same_v<long long, bzt::underlying_type_t<EnumWithUnderlyingLongLong>>);
    static_assert(bzt::is_same_v<unsigned char, bzt::underlying_type_t<EnumWithUnderlyingUChar>>);
    static_assert(bzt::is_same_v<unsigned short, bzt::underlying_type_t<EnumWithUnderlyingUShort>>);
    static_assert(bzt::is_same_v<unsigned int, bzt::underlying_type_t<EnumWithUnderlyingUInt>>);
    static_assert(bzt::is_same_v<unsigned long, bzt::underlying_type_t<EnumWithUnderlyingULong>>);
    static_assert(bzt::is_same_v<unsigned long long, bzt::underlying_type_t<EnumWithUnderlyingULongLong>>);
}

int main() {return EXIT_SUCCESS;}
