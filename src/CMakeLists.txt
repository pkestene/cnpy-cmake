# default behavior is to enable building shared library
# static library is always enabled
set (BUILD_SHARED TRUE)

# but if cross-compile target is LEON3, disable shared library building
if (CMAKE_CROSSCOMPILING)

  # test if we are cross-compiling for leon
  string(COMPARE EQUAL ${MY_CROSS_COMPILE_TARGET} "sparc-gaisler-elf" is_leon)

  if (is_leon)
    set(BUILD_SHARED FALSE)
  endif (is_leon)

endif (CMAKE_CROSSCOMPILING)

# setup the list of targets to install
set (INSTALL_TARGETS cnpy-static)
if (BUILD_SHARED)
  set(INSTALL_TARGETS ${INSTALL_TARGETS} cnpy)
endif (BUILD_SHARED)

######################################################################
#
# define SHARED library target : cnpy
#
######################################################################
if (BUILD_SHARED)

  add_library(cnpy SHARED "")

  target_sources(cnpy
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/cnpy.cpp)

  target_include_directories(cnpy
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
    )

  target_link_libraries(cnpy PUBLIC ZLIB::ZLIB)

  set_target_properties(cnpy PROPERTIES LINKER_LANGUAGE CXX)

  add_library(cnpy::cnpy ALIAS cnpy)

endif(BUILD_SHARED)

######################################################################
#
# define STATIC library target : cnpy
#
######################################################################
add_library(cnpy-static STATIC "")

target_sources(cnpy-static
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/cnpy.cpp)

target_include_directories(cnpy-static
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
  )

target_link_libraries(cnpy-static PUBLIC ZLIB::ZLIB)

set_target_properties(cnpy-static PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(cnpy-static PROPERTIES OUTPUT_NAME cnpy)

add_library(cnpy::cnpy-static ALIAS cnpy-static)


##########################################################################
#
# Generate CMake own package config file as well as and regular pkg-config
#
##########################################################################
include(CMakePackageConfigHelpers)

# setup some variables
set(version_config ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake)
set(project_config_src ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}-config.cmake.in)
set(project_config_dst ${PROJECT_BINARY_DIR}/src/${PROJECT_NAME}-config.cmake)
set(targets_export_name ${PROJECT_NAME}-targets)


# important variables
set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} CACHE STRING
  "Installation directory for libraries, relative to ${CMAKE_INSTALL_PREFIX}.")

set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE STRING
  "Installation directory for include files, relative to ${CMAKE_INSTALL_PREFIX}.")

set(INSTALL_PKGCONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/pkgconfig CACHE PATH
  "Installation directory for pkgconfig (.pc) files, relative to ${CMAKE_INSTALL_PREFIX}.")

set(INSTALL_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake CACHE STRING
  "Installation directory for cmake files, relative to ${CMAKE_INSTALL_PREFIX}.")

# Generate the version, config and target files into the build directory.
write_basic_package_version_file(
  ${version_config}
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

# generate pkg-config file
generate_pkg_config(cnpy)

# generate cmake my_package-config.cmake file
configure_package_config_file(
  ${project_config_src}
  ${project_config_dst}
  INSTALL_DESTINATION ${INSTALL_CMAKE_DIR})
  # Use a namespace because CMake provides better diagnostics
  # for namespaced imported targets.
export(
  TARGETS ${INSTALL_TARGETS} NAMESPACE cnpy::
  FILE ${PROJECT_BINARY_DIR}/${targets_export_name}.cmake)

################################################################
#
# Install
#
################################################################

#
# Install version, config and target files.
#
install(
  FILES ${project_config_dst} ${version_config}
  DESTINATION ${INSTALL_CMAKE_DIR})

install(
  EXPORT ${targets_export_name}
  DESTINATION ${INSTALL_CMAKE_DIR}
  NAMESPACE cnpy::)

#
# install the pkg-config file
#
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/cnpy.pc
  DESTINATION "${INSTALL_PKGCONFIG_DIR}")

#
# install libraries and headers
#
install(
  TARGETS ${INSTALL_TARGETS}
  EXPORT ${targets_export_name}
  LIBRARY DESTINATION ${INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

#
# install headers (exclude cpp files)
#
install(
  FILES cnpy.h
  DESTINATION ${INSTALL_INCLUDEDIR})


