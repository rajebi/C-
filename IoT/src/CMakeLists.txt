# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project(IoT)


# ${PROJECT_SOURCE_DIR} is defined in cmake, it points to the directory where the toplevel CMakeList.txt exists.
set(INC_DIR ${PROJECT_SOURCE_DIR}/../inc)

include_directories(${INC_DIR})
#include_directories(${PROJECT_SOURCE_DIR}/../inc)
add_executable(a IoTDevice.cpp)  # this will generate a.exe output file