cmake_minimum_required(VERSION 3.19)
project(exercise2)

set(CMAKE_CXX_STANDARD 20)

add_executable(exercise2
        emails.txt
        regex-filter.cpp)
