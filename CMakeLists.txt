cmake_minimum_required(VERSION 3.14.1)

project(cmake_trivial_2023 C CXX)

set (CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)

include(FetchContent)

# Settings for `googletest`.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
option(BUILD_GMOCK OFF)

# The helper to clone a dependency, or use it from a sibling dir if available.
function(add_local_dep_or_clone dep remote tag)
  if(EXISTS "${CMAKE_CURRENT_DIR}/../${dep}" AND IS_DIRECTORY "${CMAKE_CURRENT_DIR}/../${dep}")
    message(STATUS "Using `${dep}` from `CMAKE_CURRENT_DIR/../${dep}'.")
    add_subdirectory("${CMAKE_CURRENT_DIR}/../${dep}" ${dep})
    message(STATUS "Using `${dep}` from `CMAKE_CURRENT_DIR/../${dep}': Configured.")
  elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../${dep}" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../${dep}")
    message(STATUS "Using `${dep}` from `CMAKE_CURRENT_SOURCE_DIR/../${dep}'.")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../${dep}" ${dep})
    message(STATUS "Using `${dep}` from `CMAKE_CURRENT_SOURCE_DIR/../${dep}': Configured.")
  else()
    message(STATUS "Cloning `${dep}` from `${remote}:${tag}`.")
    FetchContent_Declare(${dep} GIT_REPOSITORY ${remote} GIT_TAG ${tag} GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(${dep})
    message(STATUS "Cloning `${dep}` from `${remote}:${tag}`: Configured.")
  endif()
endfunction()

# TODO(dkorolev): Replace by `stable` of `c5t/current`.
add_local_dep_or_clone(current https://github.com/dkorolev/current gentle_cmake)
add_local_dep_or_clone(googletest https://github.com/c5t/googletest v1.14)

# Declare libraries as library targets. And add them into the `ALL_LIBRARIES` list.
set(ALL_LIBRARIES "Threads::Threads" "C5T")
file(GLOB_RECURSE LIBRARY_SOURCE_FILES "src/lib_*.cc")
foreach(LIBRARY_SOURCE_FILE ${LIBRARY_SOURCE_FILES})
  get_filename_component(LIBRARY_TARGET_NAME "${LIBRARY_SOURCE_FILE}" NAME_WE)
  add_library(${LIBRARY_TARGET_NAME} "${LIBRARY_SOURCE_FILE}") 
  list(APPEND ALL_LIBRARIES "${LIBRARY_TARGET_NAME}")
endforeach()

# Declare binaries as binary targets. And link them against all the libraries.
file(GLOB_RECURSE BINARY_SOURCE_FILES "src/*.cc")
foreach(BINARY_SOURCE_FILE ${BINARY_SOURCE_FILES})
  get_filename_component(BINARY_TARGET_NAME "${BINARY_SOURCE_FILE}" NAME_WE)
  if(NOT (BINARY_TARGET_NAME MATCHES "^lib_.*$" OR BINARY_TARGET_NAME MATCHES "^test_.*$"))
    add_executable(${BINARY_TARGET_NAME} "${BINARY_SOURCE_FILE}") 
    target_link_libraries(${BINARY_TARGET_NAME} PRIVATE "${ALL_LIBRARIES}")
  endif()
endforeach()

# Declare tests as test targets. And link them against all the libraries.
enable_testing()
file(GLOB_RECURSE TEST_SOURCE_FILES "src/test_*.cc")
foreach(TEST_SOURCE_FILE ${TEST_SOURCE_FILES})
  get_filename_component(TEST_TARGET_NAME "${TEST_SOURCE_FILE}" NAME_WE)
  add_executable(${TEST_TARGET_NAME} "${TEST_SOURCE_FILE}") 
  target_link_libraries(${TEST_TARGET_NAME} PRIVATE gtest_main "${ALL_LIBRARIES}")
  add_test(NAME ${TEST_TARGET_NAME} COMMAND ${TEST_TARGET_NAME})
endforeach()
