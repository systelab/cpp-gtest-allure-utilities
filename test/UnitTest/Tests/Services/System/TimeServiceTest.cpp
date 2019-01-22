#include "GTestAllureUtilities/Services/System/TimeService.h"

#include <chrono>
#include <gtest/gtest.h>
#include <thread>


using namespace systelab::gtest_allure_utilities;

namespace systelab { namespace gtest_allure_utilities { namespace unit_test {

	class TimeServiceTest : public testing::Test
	{
	protected:
		service::TimeService m_service;
	};


	TEST_F(TimeServiceTest, testGetCurrentTimeReturnsGreaterOrEqualTimeOnSecondCall)
	{
		time_t currentTime1 = m_service.getCurrentTime();
		time_t currentTime2 = m_service.getCurrentTime();
		ASSERT_GE(currentTime2, currentTime1);
	}

	TEST_F(TimeServiceTest, testGetCurrentTimeReturnsTime2SecondsGreaterAfterWaiting2Seconds)
	{
		time_t currentTime1 = m_service.getCurrentTime();
		std::this_thread::sleep_for(std::chrono::seconds(2));
		time_t currentTime2 = m_service.getCurrentTime();

		ASSERT_GE(currentTime2, currentTime1+2);
	}

}}}
