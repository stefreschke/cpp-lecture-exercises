cmake_minimum_required(VERSION 3.19)
project(exercise2)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(exercise2
        graph-test.cpp
        Graph.cpp
        Graph.h
        GraphFactory.cpp
        GraphFactory.h
        InstanceCounter.cpp
        InstanceCounter.h)
