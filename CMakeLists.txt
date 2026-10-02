cmake_minimum_required(VERSION 3.20)

project(LiDAR2D)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)


# =========================
# LidarSim
# =========================

add_executable(LidarSim
    src/LidarSim.cpp
    src/LidarUtils.cpp
)

target_include_directories(LidarSim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)


# =========================
# Tests
# =========================

add_executable(LidarTests
    test/LookUpTableTest.cpp
)

target_include_directories(LidarTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(LidarTests PRIVATE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(LidarTests)
