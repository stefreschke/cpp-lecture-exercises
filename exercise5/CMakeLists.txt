cmake_minimum_required(VERSION 3.6)
project(sedp_exercise5)

set(CMAKE_CXX_STANDARD 20)


add_executable(signal
    signal/main.cpp
)


add_executable(variant
    variant/main.cpp
)


add_executable(collect
    collect/main.cpp
)


add_executable(template-refactoring
    template-refactoring/main.cpp
)
