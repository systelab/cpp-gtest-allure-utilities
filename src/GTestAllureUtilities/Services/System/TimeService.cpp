#include "TimeService.h"

#include <ctime>


namespace systelab { namespace gtest_allure_utilities { namespace service {

	TimeService::TimeService()
	{
	}

	time_t TimeService::getCurrentTime() const
	{
		return std::time(0);
	}

}}}
