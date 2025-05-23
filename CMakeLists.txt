cmake_minimum_required(VERSION 3.11)

# Set the project name and version
project(avl-tree VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(tree)
add_subdirectory(benchmarking)
