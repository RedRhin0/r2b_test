cmake_minimum_required(VERSION 3.10)
project(r2b_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(r2b_test main.cpp geom3d.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
