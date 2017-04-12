cmake_minimum_required(VERSION 3.6)
project(20ThreadedHomework)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hw1.cpp)
add_executable(20ThreadedHomework ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")