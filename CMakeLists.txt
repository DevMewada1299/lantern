# ══════════════════════════════════════════════════════════════════
# MiniTorch - A PyTorch-like tensor library in C++
# ══════════════════════════════════════════════════════════════════
cmake_minimum_required(VERSION 3.20)

project(MiniTorch
    VERSION 0.1.0
    LANGUAGES CXX OBJCXX  # OBJCXX needed for Metal (.mm files)
    DESCRIPTION "Deep learning tensor library for Apple Silicon"
)

# ── C++ Standard ─────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # use -std=c++20, not -std=gnu++20

# ── Build type ───────────────────────────────────────────────────
# CLion defaults to Debug, but you can change it in CLion settings
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# ── Apple Silicon Frameworks ─────────────────────────────────────
if(APPLE)
    find_library(ACCELERATE_FRAMEWORK Accelerate REQUIRED)
    find_library(METAL_FRAMEWORK Metal REQUIRED)
    find_library(FOUNDATION_FRAMEWORK Foundation REQUIRED)
    find_library(METALPERFORMANCESHADERS_FRAMEWORK MetalPerformanceShaders REQUIRED)
    
    message(STATUS "Found Accelerate: ${ACCELERATE_FRAMEWORK}")
    message(STATUS "Found Metal: ${METAL_FRAMEWORK}")
else()
    message(WARNING "Not on Apple platform - MPS backend will not be available")
endif()

# ── Compiler Flags ───────────────────────────────────────────────
# These are ADDED to CLion's defaults, not replacing them

add_compile_options(
    # Warnings (catch bugs early)
    -Wall                   # enable most warnings
    -Wextra                 # extra warnings
    -Wpedantic              # ISO C++ compliance
    -Wconversion            # implicit conversions that might lose precision
    -Wsign-conversion       # sign conversions
    
    # Not errors (too strict for development)
    # -Werror               # uncomment for CI/CD
)

# Platform-specific optimizations
if(APPLE)
    add_compile_options(
        -march=native       # use all CPU features (AMX, NEON)
        -mtune=native
    )
endif()

# Build-type specific flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
        -g                  # debug symbols
        -O0                 # no optimization (faster compile, easier debug)
        -fno-omit-frame-pointer  # better stack traces
    )
    add_compile_definitions(
        DEBUG               # you can use #ifdef DEBUG
        MT_DEBUG=1
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(
        -O3                 # aggressive optimization
        -ffast-math         # allow floating-point reassociation
        -DNDEBUG            # disable asserts
    )
endif()

# ── Include Directories ──────────────────────────────────────────

include_directories(${CMAKE_SOURCE_DIR}/include)

# ── Main Library ─────────────────────────────────────────────────
add_library(minitorch STATIC
    # Core
    src/core/allocator.cpp
    src/core/storage.cpp
        simple_test_dtype.cpp
        simple_test_dtype.hpp

        # More files will be added in later phases:
    # src/tensor.cpp
    # src/autograd/engine.cpp
    # src/ops/cpu_ops.cpp
    # src/ops/mps_ops.mm
    # src/nn/linear.cpp
)

target_include_directories(minitorch
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

if(APPLE)
    target_link_libraries(minitorch
        PUBLIC
            ${ACCELERATE_FRAMEWORK}
            ${METAL_FRAMEWORK}
            ${FOUNDATION_FRAMEWORK}
            ${METALPERFORMANCESHADERS_FRAMEWORK}
    )
endif()

# ── Testing Framework ────────────────────────────────────────────
# We use Catch2 - it's header-only and CLion has great support for it

# Download Catch2 automatically (no manual install needed)
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2  # latest stable as of early 2025
)
FetchContent_MakeAvailable(Catch2)

# CLion integration: this makes CLion detect tests automatically
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

# ── Test Executables ─────────────────────────────────────────────
# One executable containing all tests
add_executable(minitorch_tests
    tests/test_main.cpp         # Catch2 main function
    tests/test_dtype.cpp
    tests/test_device.cpp
    tests/test_allocator.cpp
    tests/test_storage.cpp
)

target_link_libraries(minitorch_tests
    PRIVATE
        minitorch
        Catch2::Catch2WithMain  # Catch2 provides main() for us
)

# This makes CLion show each TEST_CASE as a separate test in the UI
catch_discover_tests(minitorch_tests)

# ── Optional: Benchmarks ─────────────────────────────────────────
# Uncomment when you want to benchmark (Phase 4+)
# add_executable(bench_matmul benchmarks/bench_matmul.cpp)
# target_link_libraries(bench_matmul minitorch)

# ── Installation (optional) ──────────────────────────────────────
# Uncomment when you want to install the library system-wide
# install(TARGETS minitorch
#     LIBRARY DESTINATION lib
#     ARCHIVE DESTINATION lib
# )
# install(DIRECTORY include/minitorch
#     DESTINATION include
# )

# ── Summary ──────────────────────────────────────────────────────
message(STATUS "──────────────────────────────────────")
message(STATUS "MiniTorch Configuration Summary")
message(STATUS "──────────────────────────────────────")
message(STATUS "Build type:    ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ compiler:  ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ standard:  C++${CMAKE_CXX_STANDARD}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "──────────────────────────────────────")