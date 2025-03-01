cmake_minimum_required(VERSION 3.30)
project(cubic_bezier_splines C)

set(CMAKE_C_STANDARD 11)

include(FetchContent)

FetchContent_Declare(
        hard_assert
        GIT_REPOSITORY https://github.com/CesarBerriot/hard_assert.git
        GIT_TAG master
)
FetchContent_MakeAvailable(hard_assert)

add_library(cubic_bezier_splines STATIC cubic_bezier_splines.c)
target_include_directories(cubic_bezier_splines PUBLIC include)
target_link_libraries(cubic_bezier_splines PRIVATE hard_assert)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(cubic_bezier_splines PRIVATE -ansi -pedantic-errors -std=c11 -Wall -Wextra)
endif()