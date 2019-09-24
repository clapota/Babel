cmake_minimum_required(VERSION 2.8.12)

SET(SERVER_DEPENDENCIES boost_thread pthread boost_system)
add_definitions("-fPIC -DDEBUG")

if (NOT $ENV{CLION_IDE})
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
endif()

macro(conan_basic_setup)
endmacro(conan_basic_setup)

file(
        GLOB_RECURSE
        sources
        *.cpp
        *.hpp
)

include_directories(${CMAKE_INCLUDE_PATH} .)

add_executable(babel_server ${sources})
target_link_libraries(babel_server ${CONAN_LIBS} ${SERVER_DEPENDENCIES})