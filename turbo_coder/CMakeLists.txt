cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(turbo_coder)

set(SOURCES turbo_coder.cpp turbo_coder.h)


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})