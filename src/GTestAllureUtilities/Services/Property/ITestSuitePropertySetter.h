#pragma once

#include <string>
#include <stdexcept>


namespace systelab { namespace gtest_allure { namespace service {

	class ITestSuitePropertySetter
	{
	public:
		virtual ~ITestSuitePropertySetter() = default;

		virtual void setProperty(const std::string& name, const std::string& value) const = 0;

	public:
		struct NoRunningTestSuiteException : std::runtime_error
		{
			NoRunningTestSuiteException()
				:std::runtime_error("No running test suite found when setting property to test suite")
			{}
		};
	};

}}}
