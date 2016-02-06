cmake_minimum_required(VERSION 2.8)

project(ci)

option(CI_COVERAGE "coverage" OFF)

enable_testing()

if(CI_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage -O0")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -coverage -O0")
    #-g -O0 -fprofile-arcs -ftest-coverage
    
    # make all tests end up in the root of the repo
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

add_subdirectory(examples/dev_testing)