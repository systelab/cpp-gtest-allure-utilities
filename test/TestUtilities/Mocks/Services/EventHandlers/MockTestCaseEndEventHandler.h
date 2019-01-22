#pragma once

#include "GTestAllureUtilities/Services/EventHandlers/ITestCaseEndEventHandler.h"

#include <gmock/gmock.h>


namespace systelab { namespace gtest_allure_utilities { namespace test_utility {

	class MockTestCaseEndEventHandler : public service::ITestCaseEndEventHandler
	{
	public:
		MockTestCaseEndEventHandler();
		virtual ~MockTestCaseEndEventHandler();

		MOCK_CONST_METHOD1(handleTestCaseEnd, void(model::Status));
	};

}}}

