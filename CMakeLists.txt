cmake_minimum_required(VERSION 3.22)
project(bazaar_traits)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_executable(Test_bazaar_traits test.cc include)
