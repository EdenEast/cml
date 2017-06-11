##
## CMAKE file for neam projects
##


# general flags
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(PROJ_FLAGS "${PROJ_FLAGS} -O0 -g3")
else(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(PROJ_FLAGS "${PROJ_FLAGS} -DNDEBUG ")
else(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  set(PROJ_FLAGS "${PROJ_FLAGS} -DNDEBUG ")
endif()

# some gcc/clang flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  set(PROJ_FLAGS "${PROJ_FLAGS} -std=c++1z -Wall -Wextra -Wno-unused-function -Wno-multichar")

  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(PROJ_FLAGS "${PROJ_FLAGS} -Og -fno-inline")
  else(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(PROJ_FLAGS "${PROJ_FLAGS} -O3 -finline-limit=100")
  else(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(PROJ_FLAGS "${PROJ_FLAGS} -Os ")
  endif()

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(PROJ_FLAGS "${PROJ_FLAGS} -std=c++1z -Wall -Wextra -Wno-unused-function -Wno-multichar")

  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(PROJ_FLAGS "${PROJ_FLAGS}")
  else(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(PROJ_FLAGS "${PROJ_FLAGS} -O3")
  else(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(PROJ_FLAGS "${PROJ_FLAGS} -Oz")
  endif()
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  set(PROJ_FLAGS "${PROJ_FLAGS} /std:c++latest")
endif()




