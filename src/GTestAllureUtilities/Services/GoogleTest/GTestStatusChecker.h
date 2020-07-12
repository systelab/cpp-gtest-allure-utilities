#pragma once

#include "IGTestStatusChecker.h"


namespace systelab { namespace gtest_allure { namespace service {

	class GTestStatusChecker : public IGTestStatusChecker
	{
	public:
		GTestStatusChecker();
		virtual ~GTestStatusChecker();

		model::Status getCurrentTestStatus() const override;
	};

}}}
