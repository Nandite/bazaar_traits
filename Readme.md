Bazaar traits
===============

This project is a standalone implementation of the C++ [metaprogramming library](https://en.cppreference.com/w/cpp/meta) using C++17. Following years
of learning about template metaprogramming and type traits, I came to the conclusion that the best way of understanding the
field was extensive practice. It is one of the easiest way to get up to speed on writing compile time algorithms and meta-functions. So a
quick way to exercise was to implement the [metaprogramming library](https://en.cppreference.com/w/cpp/meta) from ground.

Unlike most of the implementation (GCC, LLVM etc.), the meta-functions in this project are divided into multiple files under 
the [include](include) directory with bases traits in their own files ([helper traits](include/helper_traits.hpp), 
[Integral constant](include/integral_constant.hpp), [logical operators](include/logical_operators.hpp)...). The bulk of
the meta-functions implementation however are inside the [bazaar_traits](include/bazaar_traits.hpp) file.

A [synopsis](include/synopsis.hpp) file containing the list of all implemented (and to be implemented) traits is also 
available.

## Usage

This repository is a standalone CMake project. You can open it with any IDE supporting CMakeLists. You can then compile
the test target. Using a sufficiently modern IDE, you can take a look of the [test files](tests) and get in live
the results of the meta-functions calls.

Depending on your compiler, you can get different results. Indeed, some traits require attributes that are only
visible by the compiler and thus need compiler support to be implemented. There is a good listing and explanation about which
meta-function need compiler support and why at this [page](https://github.com/Quuxplusone/from-scratch/blob/master/include/scratch/bits/type-traits/compiler-magic.md).
When compiler support is not mandatory and not available, there are fallbacks on internal implementations of the traits 
that try to stick at most to the C++ specifications. Otherwise, a shallow implementation is used or in certain case the 
result is literally deactivated using false_type (equivalent to systematically return false at function calls).

This implementation has been tested using the following compilers:
- gcc 9.4.0
- Clang 10
- Clang 14

## Caution

Please, do not use the code of this project into production. Use instead the facilities provided through the standard
library of your C++ compiler. This repository is first and foremost for learning purposes.

## CppCon talks

If you want to learn about metaprogramming, i advice watching the CppCon talks of [Walter E. Brown](https://cppcon2019.sched.com/speaker/walter_e_brown) and [Jody Hagins](https://cppcon2020.sched.com/speaker/cppcon.2020.coachhagins_gmail.com) about the subject:
- Modern Template Metaprogramming: A Compendium [Part 1](https://www.youtube.com/watch?v=Am2is2QCvxY) & [Part 2](https://www.youtube.com/watch?v=a0FliKwcwXE).
- Template Metaprogramming: Type Traits [Part 1](https://www.youtube.com/watch?v=tiAVWcjIF6o) & [Part 2](https://www.youtube.com/watch?v=dLZcocFOb5Q).

These talks require a good knowledge of C++ and template programming. They are not intended for beginners.

## Feedback

Don't hesitate if you have any suggestions for improving this project, or if you find any error. I will be glad to
hear from you. There are traits that have been implemented yet. You can submit implementations suggestions.
Contributions are welcomed :)

## License

Distributed under the MIT Software License (X11 license).
See accompanying file LICENSE.