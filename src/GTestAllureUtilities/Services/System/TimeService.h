#pragma once

#include "ITimeService.h"


namespace systelab { namespace gtest_allure { namespace service {

	class TimeService : public ITimeService
	{
	public:
		TimeService();
		virtual ~TimeService() = default;

		time_t getCurrentTime() const;
	};

}}}
