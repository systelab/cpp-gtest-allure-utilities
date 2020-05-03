#pragma once

#include "GTestAllureUtilities/Services/EventHandlers/ITestCaseEndEventHandler.h"


namespace systelab { namespace gtest_allure { namespace test_utility {

	class MockTestCaseEndEventHandler : public service::ITestCaseEndEventHandler
	{
	public:
		MockTestCaseEndEventHandler();
		virtual ~MockTestCaseEndEventHandler();

		MOCK_CONST_METHOD1(handleTestCaseEnd, void(model::Status));
	};

}}}

