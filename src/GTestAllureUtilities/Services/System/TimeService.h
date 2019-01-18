#pragma once

#include "ITimeService.h"


namespace systelab { namespace gtest_allure_utilities { namespace service {

	class TimeService : public ITimeService
	{
	public:
		TimeService();
		virtual ~TimeService() = default;

		time_t getCurrentTime() const;
	};

}}}
