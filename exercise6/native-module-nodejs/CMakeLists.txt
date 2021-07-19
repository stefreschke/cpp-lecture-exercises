cmake_minimum_required(VERSION 3.6)
project(sedp_exercise6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

#set(DEFAULT_PROJECT_OPTIONS "")

add_library(process SHARED
    process.cpp
)

target_include_directories(process
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

#set_target_properties(process
#    PROPERTIES
#    ${DEFAULT_PROJECT_OPTIONS}
#    PREFIX ""
#    SUFFIX ".node"
#)
