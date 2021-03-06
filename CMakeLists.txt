cmake_minimum_required(VERSION 2.6)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

project(distributions)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g -std=c++0x")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-sign-compare -Wno-strict-aliasing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -mfpmath=sse -msse4.1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -funsafe-math-optimizations")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx") # on sandy bridge and later
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-trapping-math -ffinite-math-only -fvect-cost-model -mrecip")
if(DEFINED ENV{CXX_FLAGS})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{CXX_FLAGS}") # for testing
endif()
message("CXX_FLAGS =${CMAKE_CXX_FLAGS}")

find_package(MKL)
if(MKL_FOUND)
  message(STATUS "Using Intel MKL")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_INTEL_MKL")
  include_directories(${MKL_INCLUDE_DIRS})
  link_directories(${MKL_LIBRARY_DIRS})
endif()

enable_testing()
include(CTest)

add_subdirectory(src)
add_subdirectory(benchmarks)
