cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
macro(conan_basic_setup)
endmacro(conan_basic_setup)


find_package(Qt5Widgets CONFIG REQUIRED)

file(
        GLOB_RECURSE
        sources
        *.cpp
        *.hpp
)

include_directories(${CMAKE_INCLUDE_PATH})
add_executable(babel_client ${sources})
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets)
