cmake_minimum_required(VERSION 3.16)

project(lab7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/qt/6.11.0/mingw_64")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

enable_testing()

add_subdirectory(subs/lab5)
add_subdirectory(tests)

add_executable(
    benchmarks
    src/benchmarks.cpp
)

target_include_directories(
    benchmarks PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)