cmake_minimum_required(VERSION 3.22)
project(bazaar_traits)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)
add_executable(Bazaar test.cc include)
