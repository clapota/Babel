cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

#if (NOT $ENV{CLION_IDE})
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
#endif()

#macro(conan_basic_setup)
#endmacro(conan_basic_setup)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(
        GLOB_RECURSE
        sources
        *.cpp
        *.hpp
        *.ui
        *.qrc
)

set(CMAKE_AUTOUIC ON)
include_directories(${CMAKE_INCLUDE_PATH} .)

add_executable(babel_client ${sources})

target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets)
