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
#include <utility>
#include "integer_sequence.hpp"

namespace bzt = bazaar::traits;

using int1 = bzt::integer_sequence<int, 1>;
using size10 = bzt::integer_sequence<std::size_t, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9>;
using unsignedInt4 = bzt::integer_sequence<unsigned int, 0, 10, 5, 8>;
using short7 = bzt::integer_sequence<short, 1, 4, 7, 8, 9, 7, 9>;
using char8 = bzt::integer_sequence<char, 9, 8, 7, 5, 11, 25, 69, 48>;
using long32 = bzt::integer_sequence<long, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
        19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32>;
using int50 = bzt::integer_sequence<int, 3, 6, 9, 12, 15, 18, 21, 24,
        27, 30, 33, 36, 39, 42, 45, 48, 51,
        54, 57, 60, 63, 66, 69, 72, 75, 78,
        81, 84, 87, 90, 93, 96, 99, 102, 105,
        108, 111, 114, 117, 120, 123, 126, 129,
        132, 135, 138, 141, 144, 147, 150>;
using ones30 = bzt::integer_sequence<int, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1>;
using zeros50 = bzt::integer_sequence<signed char, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0>;
using unsignedCharRange = bzt::integer_sequence<unsigned char, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
        43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
        71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
        100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,
        123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145,
        146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
        170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193,
        194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217,
        218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241,
        242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255>;

using unsignedChar255 = bzt::integer_sequence<unsigned char, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
        43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
        71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
        100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,
        123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145,
        146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
        170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193,
        194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217,
        218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241,
        242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254>;

[[maybe_unused]] void test_is_integer_sequence_type() {

    static_assert(bzt::is_same_v<int1::value_type, int>);
    static_assert(bzt::is_same_v<size10::value_type, std::size_t>);
    static_assert(bzt::is_same_v<unsignedInt4::value_type, unsigned int>);
    static_assert(bzt::is_same_v<short7::value_type, short>);
    static_assert(bzt::is_same_v<char8::value_type, char>);
    static_assert(bzt::is_same_v<long32::value_type, long>);
    static_assert(bzt::is_same_v<int50::value_type, int>);
    static_assert(bzt::is_same_v<ones30::value_type, int>);
    static_assert(bzt::is_same_v<zeros50::value_type, signed char>);
    static_assert(bzt::is_same_v<unsignedCharRange::value_type, unsigned char>);

    static_assert(int1::size() == 1);
    static_assert(size10::size() == 10);
    static_assert(unsignedInt4::size() == 4);
    static_assert(short7::size() == 7);
    static_assert(char8::size() == 8);
    static_assert(int1::size() == 1);
    static_assert(long32::size() == 32);
    static_assert(int50::size() == 50);
    static_assert(ones30::size() == 30);
    static_assert(zeros50::size() == 50);
    static_assert(unsignedCharRange::size() == 256);
}

[[maybe_unused]] void test_is_integer_sequence_helpers() {

    using makeInt1 = bzt::make_integer_sequence<int, 1>;
    using makeIndex7 = bzt::make_index_sequence<7>;
    using makeInt12 = bzt::make_integer_sequence<int, 12>;
    using makeShort7 = bzt::make_integer_sequence<short, 7>;
    using makeUnsignedChar256 = bzt::make_integer_sequence<unsigned char, 255>;
    using makeFor5 = bzt::index_sequence_for<short, int, const long, unsigned, volatile signed>;

    static_assert(makeInt1::size() == bzt::integer_sequence<int, 0>::size());
    static_assert(makeIndex7::size() == bzt::integer_sequence<std::size_t, 0,1,2,3,4,5,6>::size());
    static_assert(makeInt12::size() == bzt::integer_sequence<int, 0,1,2,3,4,5,6,7,8,9,10,11>::size());
    static_assert(makeShort7::size() == bzt::integer_sequence<short, 0,1,2,3,4,5,6>::size());
    static_assert(makeUnsignedChar256::size() == unsignedCharRange::size() - 1); // make_integer_sequence generates a sequence 0, 1, 2, ..., N-1
    static_assert(makeUnsignedChar256::size() == unsignedChar255::size());
    static_assert(makeFor5::size() == bzt::integer_sequence<short, 0,1,2,3,4>::size());

    static_assert(bzt::is_same_v<makeInt1, bzt::integer_sequence<int, 0>>);
    static_assert(bzt::is_same_v<makeIndex7, bzt::integer_sequence<std::size_t, 0,1,2,3,4,5,6>>);
    static_assert(bzt::is_same_v<makeIndex7, bzt::index_sequence<0,1,2,3,4,5,6>>);
    static_assert(bzt::is_same_v<makeInt12, bzt::integer_sequence<int, 0,1,2,3,4,5,6,7,8,9,10,11>>);
    static_assert(bzt::is_same_v<makeShort7, bzt::integer_sequence<short, 0,1,2,3,4,5,6>>);
    static_assert(bzt::is_same_v<makeUnsignedChar256, unsignedChar255>);
    static_assert(bzt::is_same_v<makeFor5, bzt::integer_sequence<std::size_t, 0,1,2,3,4>>);
    static_assert(bzt::is_same_v<makeFor5, bzt::index_sequence<0,1,2,3,4>>);
}

int main() {return EXIT_SUCCESS;}