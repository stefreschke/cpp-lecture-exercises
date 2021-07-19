cmake_minimum_required(VERSION 3.6)
project(sedp_exercise6)

set(CMAKE_CXX_STANDARD 20)

#set(DEFAULT_PROJECT_OPTIONS "")

add_executable(script-embedding-duktape
    main.cpp
)

#target_include_directories(script-embedding-duktape
#    PRIVATE
#)

#set_target_properties(script-embedding-duktape
#    PROPERTIES
#    ${DEFAULT_PROJECT_OPTIONS}
#)
