#include "stdafx.h"
#include "GTestAllureUtilities/AllureAPI.h"


using namespace testing;

namespace systelab { namespace gtest_allure { namespace sample_project {

	class ComplexTestSuite : public testing::Test
	{
		void SetUp()
		{
			AllureAPI::setTMSId("TC-AT-PROJ-001");
			AllureAPI::setTestSuiteDescription("This is the description for the ComplexTestSuite");
		}
	};

	TEST_F(ComplexTestSuite, testCase1)
	{
		AllureAPI::setTestSuiteName("Perform a sum between two numbers");

		unsigned int sum;
		AllureAPI::addAction("Calculate sum 100 plus 23", [&sum]() -> void
		{
			sum = 100 + 23;
		});

		AllureAPI::addExpectedResult("Sum value is 123", [sum]() -> void
		{
			ASSERT_EQ(123, sum);
		});
	}

	TEST_F(ComplexTestSuite, testCase2)
	{
		AllureAPI::setTestSuiteName("Performs a series of arithmetic operations");

		unsigned int total;
		AllureAPI::addAction("Calculate total 25 plus 14", [&total]() -> void
		{
			total = 25 + 14;
		});

		AllureAPI::addAction("Add 10 to total", [&total]() -> void
		{
			total += 10;
		});

		AllureAPI::addAction("Remove 7 from total", [&total]() -> void
		{
			total -= 7;
		});

		AllureAPI::addExpectedResult("Total is 42", [total]() -> void
		{
			ASSERT_EQ(42, total);
		});

		AllureAPI::addAction("Remove 42 from total", [&total]() -> void
		{
			total -= 42;
		});

		AllureAPI::addExpectedResult("Total is 0", [total]() -> void
		{
			ASSERT_EQ(0, total);
		});
	}

}}}
