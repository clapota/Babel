cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

file(
        GLOB_RECURSE
        sources
        *.cpp
        *.hpp
)

include_directories(${CMAKE_INCLUDE_PATH} .)
add_library(babel_common STATIC ${sources})
