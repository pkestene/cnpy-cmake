cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED PROJECT_NAME)
  set(CNPY_IS_TOP_LEVEL ON)
else()
  set(CNPY_IS_TOP_LEVEL OFF)
endif()

project(cnpy VERSION 0.2.0 LANGUAGES C CXX)

# set default build type
include(cmake/set_build_type.cmake)

option(CNPY_BUILD_TESTS "Build tests" ON)

# always export compile commands database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set C++14 standard as default
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# zlib is required as a public dependency
find_package(ZLIB REQUIRED)

# gnu compatibility,
# see https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)

# macro helper to generate pkg-config file
include(cmake/generate_pkg_config.cmake)

# build sources
add_subdirectory(src)
add_subdirectory(example)

if(CNPY_BUILD_TESTS AND CNPY_IS_TOP_LEVEL)
  include(CTest)
  add_subdirectory(tests)
endif()


##################### PRINT CONFIGURE STATUS ######################
message("//===================================================")
message("// ${PROJECT_NAME} build configuration:")
message("// ${PROJECT_NAME} version : ${PROJECT_VERSION}")
message("//===================================================")
message("  CMake version          : ${CMAKE_VERSION}")
if (NOT CMAKE_BUILD_TYPE)
  message("  CMake build type       : NOT SET !")
else()
  message("  CMake build type       : ${CMAKE_BUILD_TYPE}")
endif()
message("  CMake install prefix   : ${CMAKE_INSTALL_PREFIX}")
message("  CMake cross-compiling  ? ${CMAKE_CROSSCOMPILING}")
if (CMAKE_CROSSCOMPILING)
  message("  cross-compiling target architecture : ${MY_CROSS_COMPILE_TARGET}")
endif()
message("  CMake system processor : ${CMAKE_SYSTEM_PROCESSOR}")
message("  CMake system name (OS) : ${CMAKE_SYSTEM_NAME}")
message("  C++ Compiler : ${CMAKE_CXX_COMPILER_ID} "
  "${CMAKE_CXX_COMPILER_VERSION} "
  "${CMAKE_CXX_COMPILER_WRAPPER}")
message("    ${CMAKE_CXX_COMPILER}")
message("")
message(" ZLIB found : ${ZLIB_FOUND}")
