#pragma once

#include "GTestAllureUtilities/Model/Status.h"

#include <string>
#include <stdexcept>


namespace systelab { namespace gtest_allure { namespace service {

	class ITestCaseEndEventHandler
	{
	public:
		virtual ~ITestCaseEndEventHandler() = default;

		virtual void handleTestCaseEnd(model::Status) const = 0;

	public:
		struct NoRunningTestCaseException : std::runtime_error
		{
			NoRunningTestCaseException()
				:std::runtime_error("No running test case found when handling event for test case end")
			{}
		};
	};

}}}
