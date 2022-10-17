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
#include "ratio.hpp"

[[maybe_unused]] void test_ratio_reduction() {
    {
        static_assert(bazaar::ratio<1, 1>::num == 1);
        static_assert(bazaar::ratio<1, 1>::den == 1);
    }
    {
        static_assert(bazaar::ratio<1, 10>::num == 1);
        static_assert(bazaar::ratio<1, 10>::den == 10);
    }
    {
        static_assert(bazaar::ratio<1, 1>::num == 1);
        static_assert(bazaar::ratio<1, 1>::den == 1);
    }
    {
        static_assert(bazaar::ratio<10, 10>::num == 1);
        static_assert(bazaar::ratio<10, 10>::den == 1);
    }
    {
        static_assert(bazaar::ratio<10, 1>::num == 10);
        static_assert(bazaar::ratio<10, 1>::den == 1);
    }
    {
        static_assert(bazaar::ratio<12, 4>::num == 3);
        static_assert(bazaar::ratio<12, 4>::den == 1);
    }
    {
        static_assert(bazaar::ratio<12, -4>::num == -3);
        static_assert(bazaar::ratio<12, -4>::den == 1);
    }
    {
        static_assert(bazaar::ratio<-12, 4>::num == -3);
        static_assert(bazaar::ratio<-12, 4>::den == 1);
    }
    {
        static_assert(bazaar::ratio<-12, -4>::num == 3);
        static_assert(bazaar::ratio<-12, -4>::den == 1);
    }
    {
        static_assert(bazaar::ratio<4, 12>::num == 1);
        static_assert(bazaar::ratio<4, 12>::den == 3);
    }
    {
        static_assert(bazaar::ratio<2, 4>::num == 1);
        static_assert(bazaar::ratio<2, 4>::den == 2);
    }
    {
        static_assert(bazaar::ratio<24, 108>::num == 2);
        static_assert(bazaar::ratio<24, 108>::den == 9);
    }
    {
        static_assert(bazaar::ratio<10, 35>::num == 2);
        static_assert(bazaar::ratio<10, 35>::den == 7);
    }
    {
        static_assert(bazaar::ratio<8, 12>::num == 2);
        static_assert(bazaar::ratio<8, 12>::den == 3);
    }
    {
        static_assert(bazaar::ratio<0x7FFFFFFFFFFFFFFFLL, 127>::num == 72624976668147841LL);
        static_assert(bazaar::ratio<0x7FFFFFFFFFFFFFFFLL, 127>::den == 1);
    }
    {
        static_assert(bazaar::ratio<-0x7FFFFFFFFFFFFFFFLL, 127>::num == -72624976668147841LL);
        static_assert(bazaar::ratio<0x7FFFFFFFFFFFFFFFLL, 127>::den == 1);
    }
    {
        static_assert(bazaar::ratio<0x7FFFFFFFFFFFFFFFLL, -127>::num == -72624976668147841LL);
        static_assert(bazaar::ratio<-0x7FFFFFFFFFFFFFFFLL, -127>::den == 1);
    }
}

[[maybe_unused]] void test_ratio_add() {
    {
        using R1 = bazaar::ratio<1, 1>;
        using R2 = bazaar::ratio<1, 1>;
        using Result = bazaar::ratio_add<R1, R2>::type;
        static_assert(Result::num == 2 && Result::den == 1);
    }
    {
        using R1 = bazaar::ratio<1, 3>;
        using R2 = bazaar::ratio<1, 3>;
        using Result = bazaar::ratio_add<R1, R2>::type;
        static_assert(Result::num == 2 && Result::den == 3);
    }
    {
        using R1 = bazaar::ratio<1, -2>;
        using R2 = bazaar::ratio<1, 1>;
        using Result = bazaar::ratio_add<R1, R2>::type;
        static_assert(Result::num == 1 && Result::den == 2);
    }
    {
        using R1 = bazaar::ratio<-1, 5>;
        using R2 = bazaar::ratio<4, 7>;
        using Result = bazaar::ratio_add<R1, R2>::type;
        static_assert(Result::num == 13 && Result::den == 35);
    }
    {
        using R1 = bazaar::ratio<42511, 3547>;
        using R2 = bazaar::ratio<8572, 9875>;
        using Result = bazaar::ratio_add<R1, R2>::type;
        static_assert(Result::num == 450201009 && Result::den == 35026625);
    }
    {
        using R1 = bazaar::ratio<-8798, 54614>;
        using R2 = bazaar::ratio<-41638, 68145>;
        using Result = bazaar::ratio_add<R1, R2>::type;
        static_assert(Result::num == -2472941 && Result::den == 3202815);
    }
    {
        using R1 = bazaar::ratio<0>;
        using R2 = bazaar::ratio<0>;
        using Result = bazaar::ratio_add<R1, R2>::type;
        static_assert(Result::num == 0 && Result::den == 1);
    }
    {
        using R1 = bazaar::ratio<1>;
        using R2 = bazaar::ratio<0>;
        using Result = bazaar::ratio_add<R1, R2>::type;
        static_assert(Result::num == 1 && Result::den == 1);
    }
}

[[maybe_unused]] void test_ratio_sub() {
    {
        using R1 = bazaar::ratio<1>;
        using R2 = bazaar::ratio<1>;
        using Result = bazaar::ratio_sub<R1, R2>::type;
        static_assert(Result::num == 0 && Result::den == 1);
    }
    {
        using R1 = bazaar::ratio<1, 2>;
        using R2 = bazaar::ratio<1, 1>;
        using Result = bazaar::ratio_sub<R1, R2>::type;
        static_assert(Result::num == -1 && Result::den == 2);
    }
    {
        using R1 = bazaar::ratio<-1, 2>;
        using R2 = bazaar::ratio<1, 1>;
        using Result = bazaar::ratio_sub<R1, R2>::type;
        static_assert(Result::num == -3 && Result::den == 2);
    }
    {
        using R1 = bazaar::ratio<1, -2>;
        using R2 = bazaar::ratio<1, 1>;
        using Result = bazaar::ratio_sub<R1, R2>::type;
        static_assert(Result::num == -3 && Result::den == 2);
    }
    {
        using R1 = bazaar::ratio<0>;
        using R2 = bazaar::ratio<0>;
        using Result = bazaar::ratio_sub<R1, R2>::type;
        static_assert(Result::num == 0 && Result::den == 1);
    }
    {
        using R1 = bazaar::ratio<1>;
        using R2 = bazaar::ratio<0>;
        using Result = bazaar::ratio_sub<R1, R2>::type;
        static_assert(Result::num == 1 && Result::den == 1);
    }
    {
        using R1 = bazaar::ratio<0>;
        using R2 = bazaar::ratio<1>;
        using Result = bazaar::ratio_sub<R1, R2>::type;
        static_assert(Result::num == -1 && Result::den == 1);
    }
    {
        using R1 = bazaar::ratio<8798, 54614>;
        using R2 = bazaar::ratio<41638, 68145>;
        using Result = bazaar::ratio_sub<R1, R2>::type;
        static_assert(Result::num == -1441031 && Result::den == 3202815);
    }
    {
        using R1 = bazaar::ratio<6514354, 1>;
        using R2 = bazaar::ratio<9876, 1>;
        using Result = bazaar::ratio_sub<R1, R2>::type;
        static_assert(Result::num == 6504478 && Result::den == 1);
    }
}

[[maybe_unused]] void test_ratio_multiply() {
    {
        using R1 = bazaar::ratio<1, 1>;
        using R2 = bazaar::ratio<1, 1>;
        using Result = bazaar::ratio_multiply<R1, R2>::type;
        static_assert(Result::num == 1 && Result::den == 1);
    }
    {
        using R1 = bazaar::ratio<1, 2>;
        using R2 = bazaar::ratio<1, 2>;
        using Result = bazaar::ratio_multiply<R1, R2>::type;
        static_assert(Result::num == 1 && Result::den == 4);
    }
    {
        using R1 = bazaar::ratio<-1, 1>;
        using R2 = bazaar::ratio<1, 1>;
        using Result = bazaar::ratio_multiply<R1, R2>::type;
        static_assert(Result::num == -1 && Result::den == 1);
    }
    {
        using R1 = bazaar::ratio<-1, 1>;
        using R2 = bazaar::ratio<-1, 1>;
        using Result = bazaar::ratio_multiply<R1, R2>::type;
        static_assert(Result::num == 1 && Result::den == 1);
    }
    {
        using R1 = bazaar::ratio<1, 2>;
        using R2 = bazaar::ratio<-1, 2>;
        using Result = bazaar::ratio_multiply<R1, R2>::type;
        static_assert(Result::num == -1 && Result::den == 4);
    }
    {
        using R1 = bazaar::ratio<81762, 2124>;
        using R2 = bazaar::ratio<39879, 871>;
        using Result = bazaar::ratio_multiply<R1, R2>::type;
        static_assert(Result::num == 181143711 && Result::den == 102778);
    }
    {
        using R1 = bazaar::ratio<9871687, 86168>;
        using R2 = bazaar::ratio<86741981, 864116>;
        using Result = bazaar::ratio_multiply<R1, R2>::type;
        static_assert(Result::num == 856289686191947LL && Result::den == 74459147488LL);
    }
}

[[maybe_unused]] void test_ratio_division() {
    {
        using R1 = bazaar::ratio<1, 1>;
        using R2 = bazaar::ratio<1, 1>;
        using Result = bazaar::ratio_divide<R1, R2>::type;
        static_assert(Result::num == 1 && Result::den == 1);
    }
    {
        using R1 = bazaar::ratio<-1, 1>;
        using R2 = bazaar::ratio<1, 1>;
        using Result = bazaar::ratio_divide<R1, R2>::type;
        static_assert(Result::num == -1 && Result::den == 1);
    }
    {
        using R1 = bazaar::ratio<1, 2>;
        using R2 = bazaar::ratio<-1, 1>;
        using Result = bazaar::ratio_divide<R1, R2>::type;
        static_assert(Result::num == -1 && Result::den == 2);
    }
    {
        using R1 = bazaar::ratio<1, 1>;
        using R2 = bazaar::ratio<1, 2>;
        using Result = bazaar::ratio_divide<R1, R2>::type;
        static_assert(Result::num == 2 && Result::den == 1);
    }
    {
        using R1 = bazaar::ratio<8189, 861768>;
        using R2 = bazaar::ratio<4187, 6818>;
        using Result = bazaar::ratio_divide<R1, R2>::type;
        static_assert(Result::num == 27916301LL && Result::den == 1804111308LL);
    }
    {
        using R1 = bazaar::ratio<98198, 715>;
        using R2 = bazaar::ratio<87165, 89189179>;
        using Result = bazaar::ratio_divide<R1, R2>::type;
        static_assert(Result::num == 8758198999442LL && Result::den == 62322975LL);
    }
}

[[maybe_unused]] void test_ratio_equals() {
    static_assert(bazaar::ratio_equal_v<bazaar::ratio<1, 1>, bazaar::ratio<1, 1>>);
    static_assert(bazaar::ratio_equal_v<bazaar::ratio<0x7FFFFFFFFFFFFFFFLL, 1>,
            bazaar::ratio<0x7FFFFFFFFFFFFFFFLL, 1>>);
    static_assert(bazaar::ratio_equal_v<bazaar::ratio<-1, 1>, bazaar::ratio<-1, 1>>);
    static_assert(bazaar::ratio_equal_v<bazaar::ratio<-1, 1>, bazaar::ratio<1, -1>>);
    static_assert(bazaar::ratio_equal_v<bazaar::ratio<0>, bazaar::ratio<0>>);
    static_assert(bazaar::ratio_equal_v<bazaar::ratio<0>, bazaar::ratio<0, 1>>);
    static_assert(bazaar::ratio_equal_v<bazaar::ratio<1, 2>, bazaar::ratio<1, 2>>);
    static_assert(bazaar::ratio_equal_v<bazaar::ratio<1, 0x7FFFFFFFFFFFFFFFLL>,
            bazaar::ratio<1, 0x7FFFFFFFFFFFFFFFLL>>);
    static_assert(bazaar::ratio_equal_v<bazaar::ratio<1, 2>, bazaar::ratio<2, 4>>);
    static_assert(bazaar::ratio_equal_v<bazaar::ratio<10, 5>, bazaar::ratio<2>>);
    static_assert(bazaar::ratio_equal_v<bazaar::ratio<9819, 816>, bazaar::ratio<3273, 272>>);
}

[[maybe_unused]] void test_ratio_less() {
    static_assert(!bazaar::ratio_less_v<bazaar::ratio<1, 1>, bazaar::ratio<1, 1>>);
    static_assert(bazaar::ratio_less_v<bazaar::ratio<0, 1>, bazaar::ratio<1, 1>>);
    static_assert(bazaar::ratio_less_v<bazaar::ratio<1, 4>, bazaar::ratio<5, 2>>);
    static_assert(bazaar::ratio_less_v<bazaar::ratio<-1, 1>, bazaar::ratio<1, 1>>);
    static_assert(!bazaar::ratio_less_v<bazaar::ratio<-1, 1>, bazaar::ratio<-1, 1>>);
    static_assert(!bazaar::ratio_less_v<bazaar::ratio<1, 1>, bazaar::ratio<-1, 1>>);
    static_assert(bazaar::ratio_less_v<bazaar::ratio<0x7FFFFFFFFFFFFFFELL, 1>,
            bazaar::ratio<0x7FFFFFFFFFFFFFFFLL, 1>>);
    static_assert(bazaar::ratio_less_v<bazaar::ratio<1, 0x7FFFFFFFFFFFFFFFLL>,
            bazaar::ratio<1, 0x7FFFFFFFFFFFFFFDLL>>);
}

[[maybe_unused]] void test_ratio_less_equals() {
    static_assert(bazaar::ratio_less_equal_v<bazaar::ratio<1, 1>, bazaar::ratio<1, 1>>);
    static_assert(bazaar::ratio_less_equal_v<bazaar::ratio<0, 1>, bazaar::ratio<1, 1>>);
    static_assert(bazaar::ratio_less_equal_v<bazaar::ratio<1, 4>, bazaar::ratio<5, 2>>);
    static_assert(bazaar::ratio_less_equal_v<bazaar::ratio<-1, 1>, bazaar::ratio<1, 1>>);
    static_assert(!bazaar::ratio_less_equal_v<bazaar::ratio<1, 1>, bazaar::ratio<-1, 1>>);
    static_assert(bazaar::ratio_less_equal_v<bazaar::ratio<-1, 1>, bazaar::ratio<-1, 1>>);
    static_assert(bazaar::ratio_less_equal_v<bazaar::ratio<1, 0x7FFFFFFFFFFFFFFFLL>,
            bazaar::ratio<1, 0x7FFFFFFFFFFFFFFFLL>>);
    static_assert(bazaar::ratio_less_equal_v<bazaar::ratio<1, 0x7FFFFFFFFFFFFFFFLL>,
            bazaar::ratio<1, 0x7FFFFFFFFFFFFFFELL>>);
}

[[maybe_unused]] void test_ratio_greater() {
    static_assert(!bazaar::ratio_greater_v<bazaar::ratio<1, 1>, bazaar::ratio<1, 1>>);
    static_assert(bazaar::ratio_greater_v<bazaar::ratio<1, 1>, bazaar::ratio<1, 2>>);
    static_assert(bazaar::ratio_greater_v<bazaar::ratio<10>, bazaar::ratio<5>>);
    static_assert(!bazaar::ratio_greater_v<bazaar::ratio<0>, bazaar::ratio<1>>);
    static_assert(!bazaar::ratio_greater_v<bazaar::ratio<0x7FFFFFFFFFFFFFFFLL, 1>,
            bazaar::ratio<0x7FFFFFFFFFFFFFFFLL, 1>>);
    static_assert(bazaar::ratio_greater_v<bazaar::ratio<0x7FFFFFFFFFFFFFFFLL>,
            bazaar::ratio<0x7FFFFFFFFFFFFFFDLL>>);
    static_assert(bazaar::ratio_greater_v<bazaar::ratio<1, 0x7FFFFFFFFFFFFFFDLL>,
            bazaar::ratio<1, 0x7FFFFFFFFFFFFFFFLL>>);
    static_assert(!bazaar::ratio_greater_v<bazaar::ratio<-1, 1>, bazaar::ratio<1, 1>>);
    static_assert(bazaar::ratio_greater_v<bazaar::ratio<1, 1>, bazaar::ratio<-1, 1>>);
    static_assert(bazaar::ratio_greater_v<bazaar::ratio<-7, 2>, bazaar::ratio<-15, 2>>);
}

[[maybe_unused]] void test_ratio_greater_equals() {
    static_assert(bazaar::ratio_greater_equal_v<bazaar::ratio<1, 1>, bazaar::ratio<1, 1>>);
    static_assert(bazaar::ratio_greater_equal_v<bazaar::ratio<-1, 1>, bazaar::ratio<1, -1>>);
    static_assert(bazaar::ratio_greater_equal_v<bazaar::ratio<1, 2>, bazaar::ratio<1, 4>>);
    static_assert(!bazaar::ratio_greater_equal_v<bazaar::ratio<1, 0x7FFFFFFFFFFFFFFFLL>,
            bazaar::ratio<1, 0x7FFFFFFFFFFFFFFDLL>>);
    static_assert(bazaar::ratio_greater_equal_v<bazaar::ratio<-1, 24>, bazaar::ratio<-7, 10>>);
    static_assert(bazaar::ratio_greater_equal_v<bazaar::ratio<0x7FFFFFFFFFFFFFFFLL>,
            bazaar::ratio<0x7FFFFFFFFFFFFFFDLL>>);
    static_assert(bazaar::ratio_greater_equal_v<bazaar::ratio<1, 2>, bazaar::ratio<1, -4>>);
    static_assert(bazaar::ratio_greater_equal_v<bazaar::ratio<1>, bazaar::ratio<1>>);
    static_assert(bazaar::ratio_greater_equal_v<bazaar::ratio<0>, bazaar::ratio<0>>);
    static_assert(bazaar::ratio_greater_equal_v<bazaar::ratio<1, 0x7FFFFFFFFFFFFFFFLL>,
            bazaar::ratio<-1, 0x7FFFFFFFFFFFFFFFLL>>);
}

int main() { return EXIT_SUCCESS; }