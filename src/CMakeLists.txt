cmake_minimum_required(VERSION 3.19)
project(MAFU)

set(MAFU_VERSION_MAJOR 1)
set(MAFU_VERSION_MINOR 0)
set(VERSION ${MAFU_VERSION_MAJOR}.${MAFU_VERSION_MINOR})
add_definitions(-DMAFU_VERSION="${MAFU_VERSION_MAJOR}.${MAFU_VERSION_MINOR}")
include(${CMAKE_CURRENT_SOURCE_DIR}/shared/MUDS/cmake_snippets/CPP14Boilerplate.cmake)
#------------------------------------------------------------------------------
# Build the JUCE library
#------------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/shared/JUCE)
#------------------------------------------------------------------------------
# Build Metaphase Shared Libraries
#------------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/shared/metaphase_core)

#------------------------------------------------------------------------------
# Build the Application
#------------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/mafu)

option(BUILD_TESTS "BUILD_TESTS" OFF)
if (BUILD_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()