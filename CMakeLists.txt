cmake_minimum_required(VERSION 3.10)
project(Raytracing)

add_compile_options(-Wall -Wextra)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_executable(inOneWeekend src/main.cxx)
