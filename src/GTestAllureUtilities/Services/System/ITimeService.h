#pragma once

#include <string>


namespace systelab { namespace gtest_allure { namespace service {

	class ITimeService
	{
	public:
		virtual ~ITimeService() = default;

		virtual time_t getCurrentTime() const = 0;
	};

}}}
