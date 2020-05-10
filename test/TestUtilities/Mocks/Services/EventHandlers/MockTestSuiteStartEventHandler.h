#pragma once

#include "GTestAllureUtilities/Services/EventHandlers/ITestSuiteStartEventHandler.h"


namespace systelab { namespace gtest_allure { namespace test_utility {

	class MockTestSuiteStartEventHandler : public service::ITestSuiteStartEventHandler
	{
	public:
		MockTestSuiteStartEventHandler();
		virtual ~MockTestSuiteStartEventHandler();

		MOCK_CONST_METHOD1(handleTestSuiteStart, void(const std::string&));
	};

}}}

