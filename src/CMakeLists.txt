cmake_minimum_required(VERSION 3.10)

project(chia-log-analysis VERSION 0.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-lstdc++fs")  


configure_file(CMakeConfig.h.in CMakeConfig.h)

add_executable(chia-log-analysis main.cpp InputHandler.cpp TimeAndDate.cpp)

target_include_directories(chia-log-analysis PUBLIC "${PROJECT_BINARY_DIR}")