#pragma once

#include "GTestAllureUtilities/Services/EventHandlers/ITestCaseStartEventHandler.h"

#include <gmock/gmock.h>


namespace systelab { namespace gtest_allure { namespace test_utility {

	class MockTestCaseStartEventHandler : public service::ITestCaseStartEventHandler
	{
	public:
		MockTestCaseStartEventHandler();
		virtual ~MockTestCaseStartEventHandler();

		MOCK_CONST_METHOD1(handleTestCaseStart, void(const std::string&));
	};

}}}

