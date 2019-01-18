#pragma once

#include <string>


namespace systelab { namespace gtest_allure_utilities { namespace service {

	class ITestCaseStartEventHandler
	{
	public:
		virtual ~ITestCaseStartEventHandler() = default;

		virtual void handleTestCaseStart(const std::string& testCaseName) const = 0;
	};

}}}
