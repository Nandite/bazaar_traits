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
#include "logical_operators.hpp"

namespace bzt = bazaar::traits;

[[maybe_unused]] void test_conjunction() {
    static_assert(bzt::conjunction_v<bzt::true_type>);
    static_assert(!bzt::conjunction_v<bzt::false_type>);
    static_assert(!bzt::conjunction_v<bzt::true_type, bzt::false_type>);
    static_assert(!bzt::conjunction_v<bzt::false_type , bzt::true_type>);
    static_assert(bzt::conjunction_v<bzt::true_type,
            bzt::true_type,
            bzt::true_type,
            bzt::true_type,
            bzt::true_type>);
    static_assert(!bzt::conjunction_v<bzt::true_type,
            bzt::true_type,
            bzt::true_type,
            bzt::true_type,
            bzt::false_type>);
    static_assert(!bzt::conjunction_v<bzt::false_type ,
            bzt::false_type,
            bzt::false_type,
            bzt::false_type,
            bzt::false_type>);
    static_assert(!bzt::conjunction_v<bzt::false_type ,
            bzt::false_type,
            bzt::false_type,
            bzt::false_type,
            bzt::true_type>);
}

[[maybe_unused]] void test_disjunction() {
    static_assert(bzt::disjunction_v<bzt::true_type>);
    static_assert(!bzt::disjunction_v<bzt::false_type>);
    static_assert(!bzt::disjunction_v<bzt::false_type , bzt::false_type>);
    static_assert(bzt::disjunction_v<bzt::false_type , bzt::true_type>);
    static_assert(bzt::disjunction_v<bzt::true_type, bzt::false_type>);
    static_assert(bzt::disjunction_v<bzt::true_type, bzt::true_type>);
    static_assert(bzt::disjunction_v<bzt::true_type,
            bzt::true_type,
            bzt::true_type,
            bzt::true_type,
            bzt::true_type>);
    static_assert(!bzt::disjunction_v<bzt::false_type,
            bzt::false_type,
            bzt::false_type,
            bzt::false_type,
            bzt::false_type>);
    static_assert(bzt::disjunction_v<bzt::true_type,
            bzt::false_type,
            bzt::false_type,
            bzt::false_type,
            bzt::false_type>);
    static_assert(bzt::disjunction_v<bzt::false_type,
            bzt::false_type,
            bzt::true_type,
            bzt::false_type,
            bzt::false_type>);
}

[[maybe_unused]] void test_negation() {
    static_assert(!bzt::negation_v<bzt::true_type>);
    static_assert(bzt::negation_v<bzt::false_type>);
}

int main() {return EXIT_SUCCESS;}