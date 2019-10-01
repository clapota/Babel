cmake_minimum_required(VERSION 2.8.12)

add_definitions("-fPIC -DDEBUG -g")
set(Boost_USE_STATIC_LIBS OFF)

file(
        GLOB_RECURSE
        sources
        *.cpp
        *.hpp
)

include_directories(${CMAKE_INCLUDE_PATH} .)
add_executable(babel_server ${sources})
target_link_libraries(babel_server ${CONAN_LIBS})