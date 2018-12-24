#pragma once

#include <string>
#include <gtest/gtest.h>

namespace systelab { namespace test_utility {

	testing::AssertionResult compareJSONs(const std::string& expected, const std::string& toTest);

}}

