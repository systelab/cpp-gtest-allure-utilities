#include "stdafx.h"


using namespace testing;

namespace systelab { namespace gtest_allure { namespace sample_project {

	class ComplexTestSuite : public testing::Test
	{
	};

	TEST_F(ComplexTestSuite, testCase1)
	{
		unsigned int result = 100 + 23;
		ASSERT_EQ(123, result);
	}

	TEST_F(ComplexTestSuite, testCase2)
	{
		unsigned int result = 100 - 20;
		ASSERT_EQ(80, result);
	}

}}}
