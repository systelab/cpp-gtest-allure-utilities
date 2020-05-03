cmake_minimum_required(VERSION 3.2)

project(GTestAllureUtilitiesPackageTestProject)

# Configure environment
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find external dependencies
find_package(GTestAllureUtilities)

# Configure test package project
set(GTEST_ALLURE_UTILITIES_PACKAGE_TEST_PROJECT GTestAllureUtilitiesPackageTest)
add_executable(${GTEST_ALLURE_UTILITIES_PACKAGE_TEST_PROJECT} GTestAllureUtilitiesExample.cpp)
target_link_libraries(${GTEST_ALLURE_UTILITIES_PACKAGE_TEST_PROJECT} GTestAllureUtilities::GTestAllureUtilities)

# Register tests
enable_testing()
add_test(NAME GTestAllureUtilitiesPackageTest COMMAND ${GTEST_ALLURE_UTILITIES_PACKAGE_TEST_PROJECT})
