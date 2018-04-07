cmake_minimum_required(VERSION 3.8)

project(cml)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/scaffold")
include(scaffold)

check_master_project(CML_MASTER_PROJECT)
option(CML_ENABLE_SAMPLES "Enable building of samples for cml" ${CML_MASTER_PROJECT})
option(CML_ENABLE_TESTS "Enable building of unit tests for cml" ${CML_MASTER_PROJECT})

file(GLOB_RECURSE cml_source_files "${CMAKE_CURRENT_LIST_DIR}/cml/*.hpp")
create_interface_library(cml
  SOURCE_LIST ${cml_source_files}
  CXX_VERSION 17
  FILTER_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/cml
)
target_include_directories(${CML_LIB} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

if(CML_ENABLE_SAMPLES)
  add_subdirectory(samples)
endif()
