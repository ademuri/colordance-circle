cmake_minimum_required(VERSION 3.11)
project(colordance-circle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

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

set( SANITIZER_FLAGS "-fsanitize=address -fsanitize=undefined")
# Set appropriate warning levels and include debug symbols.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g ${SANITIZER_FLAGS}")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS_DEBUG} ${SANITIZER_FLAGS}")

file(GLOB LIBRARY_SOURCES "lib/generic/*.cpp" "lib/generic/interface/*.cpp" "lib/generic/interface/effects/*.cpp" "lib/generic/control-pole/*.cpp" "lib/generic/helper-pole/*.cpp" "lib/fake-param-controller/*.cpp" "lib/fake-environment-controller/*.cpp" "lib/runner/*.cpp" "lib/timer/*.cpp")
add_library(generic ${LIBRARY_SOURCES})
target_link_libraries(generic fake-fast-led)

target_include_directories(generic PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/generic>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/fake-param-controller>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/environment-controller>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/fake-environment-controller>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/runner>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/timer>
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
