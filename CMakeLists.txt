cmake_minimum_required(VERSION 3.16)
project(2023_advent_of_code)


include(FetchContent)


FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(range-v3
  GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
  GIT_TAG master
)
FetchContent_MakeAvailable(range-v3)

#find_package(fmt REQUIRED)
#find_package(range-v3 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

link_libraries(fmt::fmt range-v3::range-v3)

add_executable(AoC01 01.cpp ParserHelper.h)

add_executable(AoC02 02.cpp ParserHelper.h)

add_executable(AoC03 03.cpp ParserHelper.h)

add_executable(AoC04 04.cpp ParserHelper.h)

add_executable(AoC05 05.cpp ParserHelper.h)
