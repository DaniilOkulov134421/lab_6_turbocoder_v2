cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(main)

set(SOURCES main.cpp)

add_executable(main ${SOURCES})

target_link_libraries(main PUBLIC turbo_coder)

