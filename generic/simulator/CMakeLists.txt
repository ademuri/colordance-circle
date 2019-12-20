# Ogre3d
find_package(OGRE 1.10 REQUIRED)
add_library(OGRE INTERFACE IMPORTED)
set_property(TARGET OGRE PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${OGRE_INCLUDE_DIRS})

# SYSTEM means that we don't get spammy compiler warnings from OGRE.
include_directories(SYSTEM ${OGRE_INCLUDE_DIRS})
link_directories(${OGRE_LIBRARY_DIRS})

# copy essential config files next to our binary where OGRE autodiscovers them
file(COPY ${OGRE_CONFIG_DIR}/plugins.cfg # ${OGRE_CONFIG_DIR}/resources.cfg
     DESTINATION ${CMAKE_BINARY_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Boost COMPONENTS system thread OPTIONAL)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

if(${Boost_FOUND})
  add_definitions(-DUSE_BOOST=1)
  message(STATUS "Using Boost")
endif()

add_executable(Simulator Simulator.cpp Simulator.hpp SimulatorLightController.cpp)
target_link_libraries(Simulator ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${Boost_LIBRARIES} ${FREETYPE_LIBRARIES} generic)

file(COPY ../../third_party/textures DESTINATION ${CMAKE_BINARY_DIR})
file(COPY config/resources.cfg DESTINATION ${CMAKE_BINARY_DIR})
