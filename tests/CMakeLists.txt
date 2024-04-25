cmake_minimum_required(VERSION 3.10)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# avoid conflicts between
# -Wpedantic being enabled and -std=c++14 and -std=gnu++14
set(CMAKE_CXX_EXTENSIONS OFF)

project(libnpy-tests)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Catch2 REQUIRED)
#find_package(Python3 REQUIRED)

add_executable(test-cnpy test-cnpy.cpp)
target_link_libraries(test-cnpy PRIVATE cnpy::cnpy Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(test-cnpy)
