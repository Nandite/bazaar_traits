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


#include <cstdlib>
#include "helper_traits.hpp"
#include "classes.hpp"

namespace bzt = bazaar::traits;

[[maybe_unused]] void test_is_same(){
    static_assert(bzt::is_same_v<void, void>);
    static_assert(bzt::is_same_v<int, int>);
    static_assert(bzt::is_same_v<int, signed int>);
    static_assert(!bzt::is_same_v<int, unsigned int>);
    static_assert(!bzt::is_same_v<int, const int>);
    static_assert(!bzt::is_same_v<int, volatile int>);
    static_assert(!bzt::is_same_v<int, const volatile int>);
    static_assert(bzt::is_same_v<float, float>);
    static_assert(bzt::is_same_v<double, double>);
    static_assert(bzt::is_same_v<Tp, Tp>);
    static_assert(bzt::is_same_v<EmptyClassType, EmptyClassType>);
    static_assert(bzt::is_same_v<EmptyStructType, EmptyStructType>);
    static_assert(bzt::is_same_v<UnionType, UnionType>);
}

[[maybe_unused]] void test_identity(){
    static_assert(bzt::is_same_v<bzt::identity<int>::type, int>);
    static_assert(bzt::is_same_v<bzt::identity<char>::type, char>);
    static_assert(bzt::is_same_v<bzt::identity<signed short>::type, signed short>);
    static_assert(bzt::is_same_v<bzt::identity<unsigned long>::type, unsigned long>);
    static_assert(bzt::is_same_v<bzt::identity<int*>::type, int*>);
    static_assert(bzt::is_same_v<bzt::identity<int[5]>::type, int[5]>);
    static_assert(bzt::is_same_v<bzt::identity<int[]>::type, int[]>);
    static_assert(bzt::is_same_v<bzt::identity<EmptyClassType>::type, EmptyClassType>);
    static_assert(bzt::is_same_v<bzt::identity<EmptyStructType>::type, EmptyStructType>);
    static_assert(bzt::is_same_v<bzt::identity<EnumWithUnderlyingUChar>::type, EnumWithUnderlyingUChar>);
    static_assert(bzt::is_same_v<bzt::identity<EnumWithUnderlyingUShort>::type, EnumWithUnderlyingUShort>);
    static_assert(bzt::is_same_v<bzt::identity<EnumWithUnderlyingInt>::type, EnumWithUnderlyingInt>);
    static_assert(bzt::is_same_v<bzt::identity<EnumType>::type, EnumType>);
    static_assert(bzt::is_same_v<bzt::identity<UnionType>::type, UnionType>);
}

template<bool, typename = void>
struct test_enable_if_with_sfinae: public std::false_type{};
template<bool condition>
struct test_enable_if_with_sfinae<condition,
        std::void_t<bzt::enable_if_t<condition, std::nullptr_t>>>:
        public std::true_type {};
[[maybe_unused]] void test_enable_if(){
    static_assert(test_enable_if_with_sfinae<true>::value);
    static_assert(!test_enable_if_with_sfinae<false>::value);
}

[[maybe_unused]] void test_conditional(){
    static_assert(bzt::is_same_v<bzt::conditional_t<true, int, void>, int>);
    static_assert(bzt::is_same_v<bzt::conditional_t<false, int, void>, void>);
    static_assert(bzt::is_same_v<bzt::conditional_t<true, std::conditional_t<true, long, short>, void>, long>);
    static_assert(bzt::is_same_v<bzt::conditional_t<true, std::conditional_t<false, long,short>, void>, short>);
}

int main() {return EXIT_SUCCESS;}