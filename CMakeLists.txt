cmake_minimum_required(VERSION 2.8)

project(FeaturePerf)

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(FEATUREPERF_DATASETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/datasets)

add_subdirectory(third-party)
add_subdirectory(src)