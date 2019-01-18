#pragma once

#include "Model/Status.h"


namespace systelab { namespace gtest_allure_utilities { namespace service {

	class ITestCaseEndEventHandler
	{
	public:
		virtual ~ITestCaseEndEventHandler() = default;

		virtual void handleTestCaseEnd(model::Status) const = 0;
	};

}}}
