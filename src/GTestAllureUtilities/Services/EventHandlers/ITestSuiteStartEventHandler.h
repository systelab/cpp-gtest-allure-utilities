#pragma once

#include <string>


namespace systelab { namespace gtest_allure { namespace service {

	class ITestSuiteStartEventHandler
	{
	public:
		virtual ~ITestSuiteStartEventHandler() = default;

		virtual void handleTestSuiteStart(const std::string& testSuiteName) const = 0;
	};

}}}
