cmake_minimum_required(VERSION 2.8)

project(multiprocess)

include_directories("../../doctest/")

add_executable(${PROJECT_NAME} main.cpp)

add_test(NO_VALGRIND NO_OUTPUT NAME ${PROJECT_NAME}_1 COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/run.py $<TARGET_FILE:${PROJECT_NAME}>)
