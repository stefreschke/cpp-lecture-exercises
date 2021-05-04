cmake_minimum_required(VERSION 3.19)
project(exercise_1_2_palindrome_checker)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_HEADERS
        palindrome-checker.h
        )
set(PROJECT_SOURCES
        palindrome-checker.cpp
        )

## import googletest
#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/refs/tags/release-1.10.0.zip
#        # URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#)
## For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)
#
#
## run tests on make
#enable_testing()
#add_executable(
#        tests ${PROJECT_SOURCES} ${PROJECT_HEADERS}
#        tests.cc ${PROJECT_SOURCES} ${PROJECT_HEADERS}
#)
#target_link_libraries(
#        tests
#        gtest_main
#)
#include(GoogleTest)
#gtest_discover_tests(tests)



# base build
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})
