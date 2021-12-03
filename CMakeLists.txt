cmake_minimum_required(VERSION 3.10)

set(PROJECT_LANGUAGES ${PROJECT_LANGUAGES} C CXX)
project(cnpy VERSION 0.2.0 LANGUAGES ${PROJECT_LANGUAGES})

# default local cmake macro repository
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

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
include(generate_pkg_config)

# build sources
add_subdirectory(src)
add_subdirectory(example)


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
