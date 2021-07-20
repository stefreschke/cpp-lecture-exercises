cmake_minimum_required(VERSION 3.16)
project(.)

set(CMAKE_CXX_STANDARD 14)

add_library (process process.cpp)

set(CMAKE_EXECUTABLE_SUFFIX ".js")
set_target_properties(process PROPERTIES LINK_FLAGS "-s
                        WASM=0 -s EXPORTED_FUNCTIONS='[_process]' -s
                        EXPORTED_RUNTIME_METHODS=cwrap")
