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
		struct Exception : std::runtime_error
		{
			Exception(const std::string& message)
				:std::runtime_error(message)
			{}
		};

		struct NoRunningTestSuiteException : Exception
		{
			NoRunningTestSuiteException()
				:Exception("No running test suite found when handling event for test case end")
			{}
		};

		struct NoRunningTestCaseActionException : Exception
		{
			NoRunningTestCaseActionException()
				:Exception("No running test case action found when handling event for test case end")
			{}
		};
	};

}}}
