#include "stdafx.h"


using namespace testing;

namespace systelab { namespace gtest_allure { namespace sample_project {

	namespace {
		struct ParametricTestSuiteData
		{
			int a;
			int b;
			int c;
		};

		std::vector<ParametricTestSuiteData> testData =
		{
			{ 1, 7, 8 },
			{ 10, 2, 12 },
			{ 34, 20, 54 },
			{ 10, 10, 20 },
		};
	}


	class ParametricTestSuite : public testing::TestWithParam<ParametricTestSuiteData>
	{
	};

	TEST_P(ParametricTestSuite, testSumReturnsExpectedResult)
	{
		ASSERT_EQ(GetParam().c, GetParam().a + GetParam().b);
	}

	INSTANTIATE_TEST_SUITE_P(Test, ParametricTestSuite, ValuesIn(testData));

}}}
