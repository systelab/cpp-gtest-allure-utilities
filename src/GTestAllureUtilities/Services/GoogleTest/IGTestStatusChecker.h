#pragma once

#include "GTestAllureUtilities/Model/Status.h"

#include <string>
#include <stdexcept>


namespace systelab { namespace gtest_allure { namespace service {

	class IGTestStatusChecker
	{
	public:
		virtual ~IGTestStatusChecker() = default;

		virtual model::Status getCurrentTestStatus() const = 0;
	};

}}}
