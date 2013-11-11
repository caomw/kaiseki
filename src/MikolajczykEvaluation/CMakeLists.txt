cmake_minimum_required(VERSION 2.6)

project(FeaturePerf)

################################################################################
# Dependencies with packages
#
# Setup DO++ libraries (which will be built from source).
set(DO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../third-party/DO-CV)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${DO_DIR}/cmake)
find_package(DO COMPONENTS 
             Core Graphics Geometry 
             Features FeatureDetectors Match
             FeatureMatching REQUIRED)
include(${DO_USE_FILE})
# Activate OpenMP if found
if (NOT APPLE)
  find_package(OpenMP) 
  if (OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  endif()
endif ()

################################################################################
# For performance measurement and empirical validation.
add_library(Stat Stat.cpp Stat.hpp)
set_property(TARGET Stat PROPERTY FOLDER FeaturePerf)

################################################################################
# Helper classes to perform studies with Mikolajczyk et al.'s dataset.
add_library(MikolajczykDataset
            MikolajczykDataset.cpp MikolajczykDataset.hpp
            StudyOnMikolajczykDataset.cpp StudyOnMikolajczykDataset.hpp)
do_use_modules(MikolajczykDataset "${DO_LIBRARIES};Stat")
set_property(TARGET MikolajczykDataset PROPERTY FOLDER FeaturePerf)

add_executable(MikolajczykDataset_test MikolajczykDataset_test.cpp)
do_use_modules(MikolajczykDataset_test
               "${DO_LIBRARIES};MikolajczykDataset")
set_property(TARGET MikolajczykDataset_test PROPERTY FOLDER FeaturePerf)
