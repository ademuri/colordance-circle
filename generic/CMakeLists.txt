cmake_minimum_required(VERSION 3.1)
project(colordance-circle LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

# Download GoogleTest for mocks and test runner.
include(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/DownloadProject/DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 UPDATE_DISCONNECTED 1
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

# Set appropriate warning levels and include debug symbols.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11 -g")

# Generate the file needed for YCM integration
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file(GLOB LIBRARY_SOURCES "*.cpp" "../third_party/FakeFastLED/*.cpp")
add_library(generic ${LIBRARY_SOURCES})

target_include_directories(generic PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:.>)

# Add FastLED as -isystem instead of -I to reduce compiler warnings.
target_include_directories(generic SYSTEM PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../third_party/FakeFastLED>
  $<INSTALL_INTERFACE:../third_party/FakeFastLED>)

set(BUILD_SIMULATOR true CACHE BOOL "Whether to build the simulator")
if(BUILD_SIMULATOR)
  add_subdirectory(simulator)
endif(BUILD_SIMULATOR)

enable_testing()

file(GLOB TEST_SOURCES "test/*.cpp" "test/*.hpp")

add_executable(generictest ${TEST_SOURCES})

target_link_libraries(generictest generic gmock_main gtest)
add_test(generictest generictest)
