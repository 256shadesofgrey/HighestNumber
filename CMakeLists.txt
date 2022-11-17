cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJ_NAME "HighestNumber")
set(PROJ_PATH ${CMAKE_CURRENT_SOURCE_DIR})

project(${PROJ_NAME} CXX)

add_executable(${PROJ_NAME} main.cpp)

target_include_directories(${PROJ_NAME} PRIVATE ${PROJ_PATH}/include)
add_library(TestArray include/TestArray.cpp)
add_library(HighestNumberCombination include/HighestNumberCombination.cpp)
target_link_libraries(${PROJ_NAME} TestArray HighestNumberCombination)
