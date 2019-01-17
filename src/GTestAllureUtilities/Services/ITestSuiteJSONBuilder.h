#pragma once

#include <string>

namespace systelab { namespace gtest_allure_utilities { namespace model {
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure_utilities { namespace service {

	class ITestSuiteJSONBuilder
	{
	public:
		virtual ~ITestSuiteJSONBuilder() = default;

		virtual void buildJSONFiles(const model::TestSuite&) const = 0;
	};

}}}
