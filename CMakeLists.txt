cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(project)

#Set C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

#Set debug flug
string(APPEND CMAKE_C_FLAGS_DEBUG " -DDEBUG_FLAG")
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -DDEBUG_FLAG")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MTd")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

#Directories
set(SRC_DIR   turbo_coder)
set(PRJCT_DIR project)
set(TESTS_DIR tests)

add_subdirectory(${SRC_DIR})
add_subdirectory(${PRJCT_DIR})
add_subdirectory(${TESTS_DIR})

include_directories(src)


