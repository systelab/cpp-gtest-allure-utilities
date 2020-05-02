cmake_minimum_required(VERSION 3.2)

# Find external dependencides
find_package(gtest)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure test utilities project
set(TEST_UTILITIES_PROJECT TestUtilities)
file(GLOB_RECURSE TEST_UTILITIES_PROJECT_SRC "*.cpp")
file(GLOB_RECURSE TEST_UTILITIES_PROJECT_HDR "*.h")
add_library(${TEST_UTILITIES_PROJECT} STATIC ${TEST_UTILITIES_PROJECT_SRC} ${TEST_UTILITIES_PROJECT_HDR})
target_link_libraries(${TEST_UTILITIES_PROJECT} GTestAllureUtilities)

# Configure source groups
foreach(FILE ${TEST_UTILITIES_PROJECT_SRC} ${TEST_UTILITIES_PROJECT_HDR})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Header Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()
