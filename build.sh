#!/bin/sh
mkdir build ; cd build && conan install .. && cmake .. -G "Unix Makefiles" && cmake –build .
