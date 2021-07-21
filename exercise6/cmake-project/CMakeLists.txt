cmake_minimum_required(VERSION 3.16)
project(cmake-project-exercise)

include(GenerateExportHeader)

add_library(geometry INTERFACE geometries/geometries.h)
string(MAKE_C_IDENTIFIER geometry geometry)
string(TOUPPER geometry geometry)
generate_export_header(geometry
        EXPORT_FILE_NAME "include/geometry/geometry_export.h"
        EXPORT_MACRO_NAME "geometry_API")

add_library(algorithms algorithms/jarvis_algorithm.cpp algorithms/line_segment_intersection.cpp)
string(MAKE_C_IDENTIFIER algorithms algorithms)
string(TOUPPER algorithms algorithms)
generate_export_header(algorithms
        EXPORT_FILE_NAME "include/algorithms/algorithms_export.h"
        EXPORT_MACRO_NAME "algorithms_API")

add_executable(lsi_test tests/line_segment_intersection_test.cpp)
add_executable(jarvis_test tests/jarvis_algorithm_test.cpp)

include_directories(${CMAKE_SOURCE_DIR}/geometries ${CMAKE_SOURCE_DIR}/algorithms ${CMAKE_SOURCE_DIR}/tests)

target_link_libraries(algorithms geometry)
target_link_libraries(jarvis_test algorithms)
target_link_libraries(lsi_test algorithms)

option(STATIC_LIBRARY "build static libraries, otherwise dynamic" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
