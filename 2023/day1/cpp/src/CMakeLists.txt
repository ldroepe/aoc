cmake_minimum_required(VERSION 3.10)
project(aoc_2023_day1)
add_executable(
    day1.out
    day1.cpp
)

target_compile_features(day1.out PRIVATE cxx_std_17)

set(PROJECT_WARNINGS
    -Wall
    -Wextra
    -Werror
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2
    -Wmisleading-indentation
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wuseless-cast
)
target_compile_options(day1.out PRIVATE ${PROJECT_WARNINGS})
