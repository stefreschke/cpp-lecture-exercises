cmake_minimum_required(VERSION 3.16)
project(cmake-project-exercise)
option(STATIC_LIBRARIES "build static libraries, otherwise dynamic" OFF)

set(CMAKE_CXX_STANDARD 11)

# header only for geometry classes (common Point)
add_library(pointy_ears INTERFACE pointy_ears.h)
target_include_directories(pointy_ears INTERFACE /)

# library for both algorithms (2 libs)
add_library(jarvis_algorithm
        jarvis_algorithm.cpp
        jarvis_algorithm.h
        )
target_link_libraries(jarvis_algorithm pointy_ears)
add_library(line_segment_intersection
        line_segment_intersection.cpp
        line_segment_intersection.h
        )
target_link_libraries(line_segment_intersection pointy_ears)

# cl-executables for both test cases
add_executable(jarvis_test
        jarvis_algorithm_test.cpp
        )
target_link_libraries(jarvis_test jarvis_algorithm)
add_executable(line_segment_test
        line_segment_intersection_test.cpp
        )
target_link_libraries(line_segment_test line_segment_intersection)
