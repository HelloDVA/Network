
# set the version
cmake_minimum_required(VERSION 3.5)

# set the proejct name
project(Documents/Network)

# -DCMAKE_BUILD_TYPE=Debug

# set the c++ version
set(CMAKE_CXX_STANDARD 17)

# set the file.exe position
set(EXECUTABLE_OUTPUT_PATH ../../bin)

# 为clangd生成文件结构信息,对于代码索引和静态分析.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add child directory
add_subdirectory(src)

