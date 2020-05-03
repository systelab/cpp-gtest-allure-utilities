enable_testing()

# Find external dependencides
find_package(JSONAdapterTestUtilities)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure unit test project
set(UNIT_TEST_PROJECT UnitTest)
file(GLOB_RECURSE UNIT_TEST_PROJECT_SRC "*.cpp")
file(GLOB_RECURSE UNIT_TEST_PROJECT_HDR "*.h")
add_executable(${UNIT_TEST_PROJECT} ${UNIT_TEST_PROJECT_SRC} ${UNIT_TEST_PROJECT_HDR})
target_link_libraries(${UNIT_TEST_PROJECT} GTestAllureUtilities TestUtilities JSONAdapterTestUtilities::JSONAdapterTestUtilities)

# Ignored missing PDBs link warning on Visual Studio
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(${UNIT_TEST_PROJECT} PROPERTIES LINK_FLAGS "/ignore:4099")
endif()

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
add_test(NAME UnitTest COMMAND ${UNIT_TEST_PROJECT})

# Additional target for code coverage analysis
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
  include(CodeCoverage)
  setup_target_for_coverage(UnitTestCoverage UnitTest coverage)
endif()
