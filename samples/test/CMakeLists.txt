
# set the name of the sample
set(SAMPLE_NAME "cml-test")

# avoid listing all the files
file(GLOB_RECURSE srcs ./*.cpp)

add_executable(${SAMPLE_NAME} ${srcs})
target_link_libraries(${SAMPLE_NAME} libcml)

  # If we are running cmake 3.6 or higher we can set the default start up project for msvc
  # https://stackoverflow.com/a/37994396
  # if (NOT(CMAKE_VERSION VERSION_LESS "3.6.0"))
  #   set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${SAMPLE_NAME})
  # endif()



