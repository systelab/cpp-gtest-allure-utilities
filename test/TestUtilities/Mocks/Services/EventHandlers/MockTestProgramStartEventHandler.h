#pragma once

#include "GTestAllureUtilities/Services/EventHandlers/ITestProgramStartEventHandler.h"

#include <gmock/gmock.h>


namespace systelab { namespace gtest_allure_utilities { namespace test_utility {

	class MockTestProgramStartEventHandler : public service::ITestProgramStartEventHandler
	{
	public:
		MockTestProgramStartEventHandler();
		virtual ~MockTestProgramStartEventHandler();

		MOCK_CONST_METHOD0(handleTestProgramStart, void());
	};

}}}

