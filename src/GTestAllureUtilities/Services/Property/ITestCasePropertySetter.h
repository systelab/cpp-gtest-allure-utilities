#pragma once

#include <string>
#include <stdexcept>


namespace systelab { namespace gtest_allure { namespace service {

	class ITestCasePropertySetter
	{
	public:
		virtual ~ITestCasePropertySetter() = default;

		virtual void setProperty(const std::string& name, const std::string& value) const = 0;

	public:
		struct NoRunningTestSuiteException : std::runtime_error
		{
			NoRunningTestSuiteException()
				:std::runtime_error("No running test suite found when setting property to test case")
			{}
		};

		struct NoRunningTestCaseException : std::runtime_error
		{
			NoRunningTestCaseException()
				:std::runtime_error("No running test case found when setting property to test case")
			{}
		};

		struct InvalidPropertyException : std::runtime_error
		{
			InvalidPropertyException(const std::string& name)
				:std::runtime_error("Invalid property '" + name + "' when setting property to test case")
			{}
		};
	};

}}}
