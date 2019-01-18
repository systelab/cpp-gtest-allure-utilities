#pragma once

#include "GTestAllureUtilities/Model/TestCase.h"
#include "GTestAllureUtilities/Services/Report/ITestCaseJSONSerializer.h"

#include <gmock/gmock.h>


namespace systelab { namespace gtest_allure_utilities { namespace test_utility {

	class MockTestCaseJSONSerializer : public service::ITestCaseJSONSerializer
	{
	public:
		MockTestCaseJSONSerializer();
		virtual ~MockTestCaseJSONSerializer();

		MOCK_CONST_METHOD1(serialize, std::string(const model::TestCase&));
	};

}}}

