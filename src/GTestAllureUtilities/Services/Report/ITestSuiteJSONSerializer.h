#pragma once

#include <string>

namespace systelab { namespace gtest_allure { namespace model {
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ITestSuiteJSONSerializer
	{
	public:
		virtual ~ITestSuiteJSONSerializer() = default;

		virtual std::string serialize(const model::TestSuite&) const = 0;
	};

}}}
