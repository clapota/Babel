cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC -g")

set(CMAKE_AUTOMOC ON)


find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

file(
        GLOB_RECURSE
        sources
        *.cpp
        *.hpp
        *.ui
)

include_directories(${CMAKE_INCLUDE_PATH} .)
add_executable(babel_client ${sources})
target_link_libraries(babel_client ${CONAN_LIBS} ${BABEL_LIBS} Qt5::Widgets Qt5::Network babel_common)
