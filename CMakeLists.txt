project(Babel)
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

if (WIN32)
	set(BABEL_LIBS Ws2_32)
else()
	set(BABEL_LIBS)
endif()

include_directories(src/common)

add_subdirectory(src/common)
add_subdirectory(src/server)
add_subdirectory(src/client)