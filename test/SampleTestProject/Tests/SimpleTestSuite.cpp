#include "stdafx.h"
#include "GTestAllureUtilities/AllureAPI.h"


using namespace testing;

namespace systelab { namespace gtest_allure { namespace sample_project {

	class SimpleTestSuite : public testing::Test
	{
		void SetUp()
		{
			AllureAPI::setTMSId("TC-AT-PROJ-002");
			AllureAPI::setTestSuiteName("Simple automated test suite");
			AllureAPI::setTestSuiteDescription("Example of how to generate a report for a simple test suite");
			AllureAPI::setTestSuiteEpic("SampleEpic");
			AllureAPI::setTestSuiteSeverity("low");

			AllureAPI::setTestSuiteLabel("OS", "Windows");
			AllureAPI::setTestSuiteLabel("appVersion", "1.0.1");
		}
	};

	TEST_F(SimpleTestSuite, testCase1)
	{
		AllureAPI::setTestCaseName("Evaluate 'value' variable");
		std::string value = "HELLO";

		AllureAPI::addExpectedResult("Value is equal to 'HELLO'", [value]() -> void
		{
			ASSERT_EQ("HELLO", value);
		});
	}

	TEST_F(SimpleTestSuite, testCase2)
	{
		AllureAPI::setTestCaseName("Evaluate boolean expression");

		AllureAPI::addExpectedResult("Boolean expression is true", []() -> void
		{
			ASSERT_TRUE(true);
		});
	}

}}}
