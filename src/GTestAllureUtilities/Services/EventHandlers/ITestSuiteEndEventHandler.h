#pragma once

#include "GTestAllureUtilities/Model/Status.h"

#include <string>
#include <stdexcept>


namespace systelab { namespace gtest_allure { namespace service {

	class ITestSuiteEndEventHandler
	{
	public:
		virtual ~ITestSuiteEndEventHandler() = default;

		virtual void handleTestSuiteEnd(model::Status) const = 0;

	public:
		struct NoRunningTestSuiteException : std::runtime_error
		{
			NoRunningTestSuiteException()
				:std::runtime_error("No running test suite found when handling event for test suite end")
			{}
		};
	};

}}}
