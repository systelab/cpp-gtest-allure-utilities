cmake_minimum_required(VERSION 3.2)

project(GTestAllureUtilities)

# Configure environment
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setup up Google test
include(ConfigureGoogleTest)
configure_google_test()

# Configure include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add subprojects
add_subdirectory(${CMAKE_SOURCE_DIR}/src/GTestAllureUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/TestUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/UnitTest)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/IntegrationTest)
