#pragma once

#include "GTestAllureUtilities/Services/EventHandlers/ITestProgramEndEventHandler.h"

#include <gmock/gmock.h>


namespace systelab { namespace gtest_allure_utilities { namespace test_utility {

	class MockTestProgramEndEventHandler : public service::ITestProgramEndEventHandler
	{
	public:
		MockTestProgramEndEventHandler();
		virtual ~MockTestProgramEndEventHandler();

		MOCK_CONST_METHOD0(handleTestProgramEnd, void());
	};

}}}

