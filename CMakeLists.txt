##
## CMAKE file for neam/...
##

cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(filter_group)
include(flags)

project(cml)

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release MinSizeRel." FORCE)
endif()

if (${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
  message(WARNING "when checking: '${CMAKE_CURRENT_BINARY_DIR}' is the same as '${PROJECT_SOURCE_DIR}'")
  message(WARNING "you are running cmake insource!!")
  message(WARNING "you should create a build folder in order to build ${PROJ_NAME} !!!")
endif()

# Checking if we are the master project or have been submoduled as a dependency
set(MASTER_PROJECT OFF)
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  set(MASTER_PROJECT ON)
endif()

option(CML_ENABLE_SAMPLES "Enable to build the samples" ${MASTER_PROJECT})

add_library(libcml INTERFACE)
target_include_directories(libcml INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)
set_compile_flags(libcml)

# Create a custom target for ide's
file(GLOB_RECURSE cml_sources "${CMAKE_CURRENT_SOURCE_DIR}/cml/*.hpp")
add_custom_target(cml SOURCES "${cml_sources}")
add_filter_group("${cml_sources}" "${CMAKE_CURRENT_SOURCE_DIR}/cml")

if (CML_ENABLE_SAMPLES)
  add_subdirectory(samples)
endif()

