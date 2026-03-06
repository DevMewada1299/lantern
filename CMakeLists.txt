cmake_minimum_required(VERSION 3.20)
project(Lantern LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library with compiled sources
add_library(lantern STATIC
        src/core/allocator.cpp
)

target_include_directories(lantern
        PUBLIC ${CMAKE_SOURCE_DIR}/include
)

target_compile_features(lantern
        PUBLIC cxx_std_20
)