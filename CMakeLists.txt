cmake_minimum_required(VERSION 3.8)
project(Looper)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(Looper ${SOURCE_FILES})

find_package(Threads REQUIRED)
target_link_libraries(Looper Threads::Threads)