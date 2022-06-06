cmake_minimum_required(VERSION 3.11)
project(colordance-circle LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-fetch-content)

# Generate the file needed for YCM integration
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include(FetchContent)
include(fetch-content-shim)
include(ExternalProject)

FetchContent_Declare(fake-fast-led
    GIT_REPOSITORY      https://github.com/ademuri/FakeFastLED.git
    GIT_TAG             master
)
FetchContent_MakeAvailable(fake-fast-led)

FetchContent_Declare(googletest
    GIT_REPOSITORY      https://github.com/google/googletest.git
    GIT_TAG             main
)
FetchContent_MakeAvailable(googletest)

# Set appropriate warning levels and include debug symbols.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11 -g")

file(GLOB LIBRARY_SOURCES "lib/generic/*.cpp" "lib/generic/interface/*.cpp" "lib/generic/interface/effects/*.cpp" "lib/generic/control-pole/*.cpp" "lib/generic/helper-pole/*.cpp")
add_library(generic ${LIBRARY_SOURCES})
target_link_libraries(generic fake-fast-led)

target_include_directories(generic PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/generic>
    $<INSTALL_INTERFACE:lib/generic>)

set(BUILD_SIMULATOR true CACHE BOOL "Whether to build the simulator")
if(BUILD_SIMULATOR)
  add_subdirectory(lib/simulator)
endif(BUILD_SIMULATOR)

enable_testing()

file(GLOB TEST_SOURCES "lib/test/*.cpp" "lib/test/*.hpp")

add_executable(generictest ${TEST_SOURCES})

target_link_libraries(generictest
  fake-fast-led
  generic
  gmock_main
  gtest)

add_test(generictest generictest)
