#include "stdafx.h"
#include "GTestAllureUtilities/AllureAPI.h"


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
		void SetUp()
		{
			AllureAPI::setTMSId("TC-AT-PROJ-003");
			AllureAPI::setTestSuiteName("Parametric test suite");
			AllureAPI::setTestSuiteDescription("Example of how to generate reports for a parametric test");
		}
	};

	TEST_P(ParametricTestSuite, testSumReturnsExpectedResult)
	{
		AllureAPI::setTestCaseName("Compute sum of " + std::to_string(GetParam().a) + " plus " + std::to_string(GetParam().b));
		auto sum = GetParam().a + GetParam().b;

		AllureAPI::addExpectedResult("Sum value is " + std::to_string(GetParam().c), [this, sum]() -> void
		{
			ASSERT_EQ(GetParam().c, sum);
		});
	}

	INSTANTIATE_TEST_SUITE_P(Test, ParametricTestSuite, ValuesIn(testData));

}}}
