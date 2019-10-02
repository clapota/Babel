project(Babel)
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(src/common)

add_subdirectory(src/common)
add_subdirectory(src/server)
add_subdirectory(src/client)