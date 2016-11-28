project(lem LANGUAGES CXX)

# Require C++11-compliant compiler; only available for CMake v. 3.1 and up
set(CMAKE_CXX_STANDARD 11)

cmake_minimum_required(VERSION 3.1)

SET(CMAKE_COLOR_MAKEFILE On)
SET(CMAKE_VERBOSE_MAKEFILE Off)

# General compile settings
IF (NOT CMAKE_BUILD_TYPE)
 SET(CMAKE_BUILD_TYPE "Debug")
 #SET(CMAKE_BUILD_TYPE "Release")
ENDIF (NOT CMAKE_BUILD_TYPE)

# GNU Specific settings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -fpic")
endif()

# CMake Modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# LEM settings
OPTION(USE_DOUBLE_PRECISION "Use double precision" ON)

# Include directories
include_directories(
  ${lem_SOURCE_DIR}/include
)

# lem executable
SET(lem_src
    src/element.cc
    src/mesh.cc
    src/main.cc
)
add_executable(lem-gmsh
               ${lem_src}
)

# Coverage
find_package(codecov)
add_coverage(lem-gmsh)
