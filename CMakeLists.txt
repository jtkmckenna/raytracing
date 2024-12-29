cmake_minimum_required(VERSION 3.10)
project(Raytracing)

add_compile_options(-Wall -Wextra -flto)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 14)

option(DISABLE_CONST_VAR "Disable const keyword on member variables" OFF)
#option(DISABLE_NOEXCEPT "Disable noexcept keyword" OFF)
#option(DISABLE_OVERRIDE "Disable override keyword" OFF)
#option(DISABLE_FINAL "Disable final keyword" OFF)
option(DISABLE_ASSUME "Disable assume keyword" OFF)
option(DISABLE_POW "Disable pow function (replace with unrolled calculation)" OFF)
option(DISABLE_CONSTEXPR "Disable constexpr keyword" OFF)
option(WARNINGS_AS_ERRORS "Treat warnings as errors" ON)

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
if (NOT DISABLE_CONSTEXPR)
    add_compile_definitions(CONSTEXPR_NOT_INLINE)
endif()
if (WARNINGS_AS_ERRORS)
    add_compile_options(-Werror)
endif()

# Add source files
file(GLOB SOURCES "src/*.cxx")
file(GLOB HEADERS "include/*.hxx")

# Build source files

include_directories(include)
add_executable(inOneWeekend mains/main.cxx ${SOURCES} ${HEADERS})
