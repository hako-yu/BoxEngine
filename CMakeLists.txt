cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

project(BoxEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(Engine)
