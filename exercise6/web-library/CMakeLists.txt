cmake_minimum_required(VERSION 3.19)
project(.)

set(CMAKE_CXX_STANDARD 14)

add_executable(weblib
        index.html
        process.cpp
        start_server.sh)
