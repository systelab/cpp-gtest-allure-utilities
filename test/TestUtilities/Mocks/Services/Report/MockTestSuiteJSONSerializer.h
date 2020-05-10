#pragma once

#include "GTestAllureUtilities/Model/TestSuite.h"
#include "GTestAllureUtilities/Services/Report/ITestSuiteJSONSerializer.h"


namespace systelab { namespace gtest_allure { namespace test_utility {

	class MockTestSuiteJSONSerializer : public service::ITestSuiteJSONSerializer
	{
	public:
		MockTestSuiteJSONSerializer();
		virtual ~MockTestSuiteJSONSerializer();

		MOCK_CONST_METHOD1(serialize, std::string(const model::TestSuite&));
	};

}}}

