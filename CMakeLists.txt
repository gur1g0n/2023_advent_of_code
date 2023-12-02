cmake_minimum_required(VERSION 3.26)
project(2023_advent_of_code)

find_package(fmt REQUIRED)
find_package(range-v3 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

link_libraries(fmt::fmt range-v3::range-v3)

add_executable(AoC01 01.cpp ParserHelper.h)

add_executable(AoC02 02.cpp ParserHelper.h)
