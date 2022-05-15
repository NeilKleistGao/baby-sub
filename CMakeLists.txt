cmake_minimum_required(VERSION 3.20)
project(baby_sub)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(baby_sub test.cc)
target_link_libraries(baby_sub ${GTEST_BOTH_LIBRARIES})
target_link_libraries(baby_sub ${CMAKE_THREAD_LIBS_INIT})