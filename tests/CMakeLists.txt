cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(tests)

set(SOURCES tests.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(googletest)

target_link_libraries(${PROJECT_NAME} PUBLIC turbo_coder gtest)
