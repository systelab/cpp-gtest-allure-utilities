#include "stdafx.h"


using namespace testing;

namespace systelab { namespace gtest_allure { namespace sample_project {

	class SimpleTestSuite : public testing::Test
	{
	};

	TEST_F(SimpleTestSuite, testCase1)
	{
		std::string value = "HELLO";
		ASSERT_EQ("HELLO", value);
	}

	TEST_F(SimpleTestSuite, testCase2)
	{
		ASSERT_TRUE(false);
	}

}}}
