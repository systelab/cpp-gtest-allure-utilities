cmake_minimum_required(VERSION 3.2)

project(GTestAllureUtilities)

# Configure environment
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Adjust compilation flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=implicit-fallthrough")
endif()

# Configure include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)

# Add subprojects
add_subdirectory(${CMAKE_SOURCE_DIR}/src/GTestAllureUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/TestUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/UnitTest)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/IntegrationTest)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/SampleTestProject)
