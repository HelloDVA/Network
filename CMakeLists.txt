cmake_minimum_required(VERSION 2.8)

# the project name
project(Documents/Network)

#SET(CMAKE_BUILD_TYPE "Debug")


# the c++ standard
set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH ../../bin)

# set the .h and source file position
set(PINE_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PINE_SRC_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)
