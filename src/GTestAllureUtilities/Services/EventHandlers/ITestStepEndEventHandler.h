#pragma once

#include "GTestAllureUtilities/Model/Status.h"

#include <string>
#include <stdexcept>


namespace systelab { namespace gtest_allure { namespace service {

	class ITestStepEndEventHandler
	{
	public:
		virtual ~ITestStepEndEventHandler() = default;

		virtual void handleTestStepEnd(model::Status) const = 0;

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
				:Exception("No running test suite found when handling event for test step end")
			{}
		};

		struct NoRunningTestCaseException : Exception
		{
			NoRunningTestCaseException()
				:Exception("No running test case found when handling event for test step end")
			{}
		};

		struct NoRunningTestStepException : Exception
		{
			NoRunningTestStepException()
				:Exception("No running test step found when handling event for test step end")
			{}
		};
	};

}}}
