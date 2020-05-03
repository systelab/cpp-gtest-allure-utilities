#pragma once

#include <string>

namespace systelab { namespace gtest_allure { namespace model {
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ITestSuiteJSONBuilder
	{
	public:
		virtual ~ITestSuiteJSONBuilder() = default;

		virtual void buildJSONFiles(const model::TestSuite&) const = 0;
	};

}}}
