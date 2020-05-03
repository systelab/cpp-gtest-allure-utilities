#pragma once

#include "GTestAllureUtilities/Services/EventHandlers/ITestProgramStartEventHandler.h"


namespace systelab { namespace gtest_allure { namespace test_utility {

	class MockTestProgramStartEventHandler : public service::ITestProgramStartEventHandler
	{
	public:
		MockTestProgramStartEventHandler();
		virtual ~MockTestProgramStartEventHandler();

		MOCK_CONST_METHOD0(handleTestProgramStart, void());
	};

}}}

