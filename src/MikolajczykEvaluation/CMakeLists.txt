cmake_minimum_required(VERSION 2.6)

project(FeaturePerf)

################################################################################
# Dependencies with packages
#
# Setup DO++ libraries (which will be built from source).
set(DO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../third-party/doplusplus)
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
# Define the SRCPATH macro from the DO.Core library.
#add_definitions(-DDATASETS_DIR=${FEATUREPERF_DATASETS_DIR})

################################################################################
# For performance measurement and empirical validation.
add_library(FeaturePerf_Stat Stat.cpp Stat.hpp)

################################################################################
# Helper classes to perform studies with Mikolajczyk et al.'s dataset.
add_library(FeaturePerf_MikolajczykDataset
            MikolajczykDataset.cpp MikolajczykDataset.hpp
            StudyOnMikolajczykDataset.cpp StudyOnMikolajczykDataset.hpp)
do_use_modules(FeaturePerf_MikolajczykDataset
               "${DO_LIBRARIES};FeaturePerf_Stat")

add_executable(FeaturePerf_MikolajczykDataset_test MikolajczykDataset_test.cpp)
do_use_modules(FeaturePerf_MikolajczykDataset_test
               "${DO_LIBRARIES};FeaturePerf_MikolajczykDataset")
