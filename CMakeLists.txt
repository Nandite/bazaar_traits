cmake_minimum_required(VERSION 3.22)
project(Bazaar)

set(CMAKE_CXX_STANDARD 17)

add_executable(Bazaar main.cpp include/bazaar_traits.hpp include/integral_constant.hpp include/arithmetic.hpp include/synopsis.hpp include/logical_operators.hpp)
