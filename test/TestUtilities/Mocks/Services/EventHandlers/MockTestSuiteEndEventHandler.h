#pragma once

#include "GTestAllureUtilities/Services/EventHandlers/ITestSuiteEndEventHandler.h"


namespace systelab { namespace gtest_allure { namespace test_utility {

	class MockTestSuiteEndEventHandler : public service::ITestSuiteEndEventHandler
	{
	public:
		MockTestSuiteEndEventHandler();
		virtual ~MockTestSuiteEndEventHandler();

		MOCK_CONST_METHOD1(handleTestSuiteEnd, void(model::Status));
	};

}}}

