enable_testing()

# Add GoogleTest to includes
include_directories("${gtest_SOURCE_DIR}/include")
include_directories("${gmock_SOURCE_DIR}/include")

# Configure unit test project
set(UNIT_TEST_PROJECT UnitTest)
file(GLOB_RECURSE UNIT_TEST_PROJECT_SRC "*.cpp")
file(GLOB_RECURSE UNIT_TEST_PROJECT_HDR "*.h")
add_executable(${UNIT_TEST_PROJECT} ${UNIT_TEST_PROJECT_SRC} ${UNIT_TEST_PROJECT_HDR})
target_link_libraries(${UNIT_TEST_PROJECT} gmock_main GTestAllureUtilities)

#Configure source groups
foreach(FILE ${UNIT_TEST_PROJECT_SRC} ${UNIT_TEST_PROJECT_HDR}) 
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

# Register unit tests
add_test(NAME UnitTests COMMAND ${UNIT_TEST_PROJECT})
