# Setup OpenCV libraries
find_package(OpenCV REQUIRED)
# Setup DO++ libraries
set(DO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../third-party/doplusplus)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${DO_DIR}/cmake)
find_package(DO COMPONENTS 
             Core Graphics Features REQUIRED)
include(${DO_USE_FILE})

add_definitions(-DDATASETS_DIR=${FEATUREPERF_DATASETS_DIR})

# Include AKAZE directory
include_directories(../../third-party/AKAZE/src/lib)
add_library(DO_AKAZE AKAZE.hpp AKAZE.cpp)
target_link_libraries(DO_AKAZE AKAZE)

# test AKAZE feature detector.
add_executable(DO_AKAZE_test AKAZE_test.cpp)
do_use_modules(DO_AKAZE_test "DO_AKAZE;${DO_LIBRARIES}")