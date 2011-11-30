cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(hackathon src/main.cpp src/wslaserfinder.cpp)

rosbuild_add_executable(vision src/vision/vision.cpp
							src/vision/ObjectDetector.cpp
							src/vision/TOHObjectDetector.cpp
							src/vision/TOHBlueCubeDetector.cpp
							src/vision/TOHGreenCubeDetector.cpp
							src/vision/TOHRedCubeDetector.cpp
							src/vision/ImageGrabber.cpp
							src/vision/CVWindow.cpp
							src/vision/Object2D.cpp
							src/vision/TOHCube.cpp
							src/vision/VisionController.cpp
							)

target_link_libraries(vision cvblob)
