cmake_minimum_required(VERSION 3.10)
project(Raytracing)

add_compile_options(-Wall -Wextra)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)

option(DISABLE_CONST_FUNC "Disable const keyword on member functions" OFF)
option(DISABLE_CONST_INPUT "Disable const keyword on input parameters" OFF)
option(DISABLE_CONST_VAR "Disable const keyword on member variables" OFF)
option(DISABLE_NOEXCEPT "Disable noexcept keyword" OFF)
option(DISABLE_OVERRIDE "Disable override keyword" OFF)
option(DISABLE_FINAL "Disable final keyword" OFF)
option(DISABLE_ASSUME "Disable assume keyword" OFF)
option(DISABLE_POW "Disable pow function (replace with unrolled calculation)" OFF)


if(DISABLE_CONST_VAR)
    add_compile_definitions(DISABLE_CONST_VAR)
endif()
if(DISABLE_NOEXCEPT)
    add_compile_definitions(DISABLE_NOEXCEPT)
endif()
if(DISABLE_OVERRIDE)
    add_compile_definitions(DISABLE_OVERRIDE)
endif()
if(DISABLE_FINAL)
    add_compile_definitions(DISABLE_FINAL)
endif()
if(DISABLE_ASSUME)
    add_compile_definitions(DISABLE_ASSUME)
endif()
if (DISABLE_POW)
    add_compile_definitions(DISABLE_POW)
endif()

# Add source files
file(GLOB SOURCES "src/*.cxx")
file(GLOB HEADERS "include/*.hxx")

# Build source files


include_directories(include)
add_executable(inOneWeekend mains/main.cxx ${SOURCES} ${HEADERS})
