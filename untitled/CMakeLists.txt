cmake_minimum_required(VERSION 2.8)

project(cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

find_package(Threads REQUIRED)

add_executable(cpp main.cpp)
target_link_libraries(cpp ${CMAKE_THREAD_LIBS_INIT})
