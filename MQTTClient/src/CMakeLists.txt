# CMakeList.txt : CMake project for MQTTClient, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.8)

project(MQTTClient)

set(INC_DIR ${PROJECT_SOURCE_DIR}/../inc)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/../lib)

include_directories(${INC_DIR} ${LIB_DIR})

# this will generate a.exe output file
add_executable(MQTTClient MQTTClient.cpp)

# note the library has to be added after add_executable to tie it to MQTTClient project
target_link_libraries(MQTTClient ${LIB_DIR}/mosquitto.lib)

