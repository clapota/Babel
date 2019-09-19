cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

#if (NOT $ENV{CLION_IDE})
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
#endif()

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
