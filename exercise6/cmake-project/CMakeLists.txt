cmake_minimum_required(VERSION 3.16)
project(cmake-project-exercise)
option(STATIC_LIBRARY "build static libraries, otherwise dynamic" ON)

include(GenerateExportHeader)

add_library(geometry INTERFACE geometries/geometries.h)
string(MAKE_C_IDENTIFIER geometry geometry_id)
string(TOUPPER geometry_id geometry_id)
generate_export_header(geometry
        EXPORT_FILE_NAME "geometry_export.h"
        EXPORT_MACRO_NAME "geometry_id_API")

if(STATIC_LIBRARY)
    add_library(algorithms STATIC algorithms/jarvis_algorithm.cpp algorithms/line_segment_intersection.cpp)
endif()

if(NOT STATIC_LIBRARY)  # shared library...
    add_library(algorithms SHARED algorithms/jarvis_algorithm.cpp algorithms/line_segment_intersection.cpp)
endif()

add_executable(lsi_test tests/line_segment_intersection_test.cpp)
add_executable(jarvis_test tests/jarvis_algorithm_test.cpp)
include_directories(geometries tests algorithms)

target_link_libraries(algorithms geometry)
target_link_libraries(jarvis_test algorithms)
target_link_libraries(lsi_test algorithms)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
