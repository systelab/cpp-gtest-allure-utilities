# Configure preprocessor definitions
add_compile_definitions(RAPIDJSON_HAS_STDSTRING=1)

# Add project folder into includes
set(GTEST_ALLURE_UTILITIES GTestAllureUtilities)
include_directories(${CMAKE_SOURCE_DIR}/src/${GTEST_ALLURE_UTILITIES})

# Configure GTestAllureUtilities static library
file(GLOB_RECURSE GTEST_ALLURE_UTILITIES_SRC "*.cpp")
file(GLOB_RECURSE GTEST_ALLURE_UTILITIES_HDR "*.h")
add_library(${GTEST_ALLURE_UTILITIES} STATIC ${GTEST_ALLURE_UTILITIES_SRC} ${GTEST_ALLURE_UTILITIES_HDR})
target_link_libraries(${GTEST_ALLURE_UTILITIES})

#Configure source groups
foreach(FILE ${GTEST_ALLURE_UTILITIES_SRC} ${GTEST_ALLURE_UTILITIES_HDR}) 
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
