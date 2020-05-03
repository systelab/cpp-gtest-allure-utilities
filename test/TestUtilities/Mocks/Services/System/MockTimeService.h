#pragma once

#include "GTestAllureUtilities/Services/System/ITimeService.h"

#include <gmock/gmock.h>


namespace systelab { namespace gtest_allure { namespace test_utility {

	class MockTimeService:  public service::ITimeService
	{
	public:
		MockTimeService();
		virtual ~MockTimeService();

		MOCK_CONST_METHOD0(getCurrentTime, time_t());
	};

}}}

