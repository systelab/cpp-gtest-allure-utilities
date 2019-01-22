#pragma once

#include "GTestAllureUtilities/Model/TestSuite.h"
#include "GTestAllureUtilities/Services/Report/ITestSuiteJSONBuilder.h"

#include <gmock/gmock.h>


namespace systelab { namespace gtest_allure_utilities { namespace test_utility {

	class MockTestSuiteJSONBuilder : public service::ITestSuiteJSONBuilder
	{
	public:
		MockTestSuiteJSONBuilder();
		virtual ~MockTestSuiteJSONBuilder();

		MOCK_CONST_METHOD1(buildJSONFiles, void(const model::TestSuite&));
	};

}}}

