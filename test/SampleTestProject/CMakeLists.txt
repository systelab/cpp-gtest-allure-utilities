enable_testing()

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure integration test project
set(SAMPLE_TEST_PROJECT SampleTestProject)
file(GLOB_RECURSE SAMPLE_TEST_PROJECT_SRC "*.cpp")
file(GLOB_RECURSE SAMPLE_TEST_PROJECT_HDR "*.h")
add_executable(${SAMPLE_TEST_PROJECT} ${SAMPLE_TEST_PROJECT_SRC} ${SAMPLE_TEST_PROJECT_HDR})
target_link_libraries(${SAMPLE_TEST_PROJECT} GTestAllureUtilities)

# Ignored missing PDBs link warning on Visual Studio
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(${SAMPLE_TEST_PROJECT} PROPERTIES LINK_FLAGS "/ignore:4099")
endif()

#Configure source groups
foreach(FILE ${SAMPLE_TEST_PROJECT_SRC} ${SAMPLE_TEST_PROJECT_HDR}) 
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
