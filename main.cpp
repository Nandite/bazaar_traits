#include <iostream>
#include <utility>
#include "include/bazaar_traits.hpp"
#include "include/arithmetic.hpp"

struct Tp {};

namespace bzt = bazaar::traits;

int main() {
    constexpr auto max{bzt::meta_max_v<45,100,12,589,2214,55,88,9929,56>};
    constexpr auto min{bzt::meta_min_v<45,100,12,589,2214,55,88,9929,56>};
    std::cout << "Maximum value is " << max << std::endl;
    std::cout << "Minimum value is " << min << std::endl;

    static_assert(bzt::is_same_v<void, bzt::conditional_t<false, int, void>>);
    static_assert(bzt::is_integral_v<bool>);

    static_assert(bzt::is_reference_v<int>);
    static_assert(bzt::is_reference_v<int&>);
    static_assert(bzt::is_reference_v<Tp&&>);
    static_assert(bzt::is_lvalue_reference_v<std::string>);
    static_assert(bzt::is_lvalue_reference_v<std::string&>);
    static_assert(bzt::is_rvalue_reference_v<Tp&&>);
    static_assert(bzt::is_rvalue_reference_v<Tp>);

    static_assert(bzt::is_assignable_v<int,int> == std::is_assignable_v<int,int>);
    static_assert(bzt::is_assignable_v<int&, const int> == std::is_assignable_v<int &, const int>);
    static_assert(std::is_arithmetic_v<int> == bzt::is_arithmetic_v<int>);
    static_assert(std::is_arithmetic_v<float> == bzt::is_arithmetic_v<float>);
    static_assert(std::is_arithmetic_v<Tp> == bzt::is_arithmetic_v<Tp>);
    static_assert(std::is_class_v<int> == bzt::is_class_v<int>);
    static_assert(std::is_class_v<Tp> == bzt::is_class_v<Tp>);

    static_assert(std::is_swappable_v<int>);
    static_assert(bzt::is_swappable_v<int>);

    return 0;
}
