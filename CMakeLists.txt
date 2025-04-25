cmake_minimum_required(VERSION 3.10)

project(JsonQueryDB VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_FILES
    src/main.cpp
    src/json_parser.cpp
    src/query_parser.cpp
)

add_executable(JsonQueryDB ${SRC_FILES})