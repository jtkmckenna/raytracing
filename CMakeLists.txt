cmake_minimum_required(VERSION 3.10)
project(Raytracing)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_executable(inOneWeekend src/main.cxx)
