#pragma once

#include <string>

namespace systelab { namespace gtest_allure_utilities { namespace model {
	class TestCase;
}}}

namespace systelab { namespace gtest_allure_utilities { namespace service {

	class ITestCaseJSONSerializer
	{
	public:
		virtual ~ITestCaseJSONSerializer() = default;

		virtual std::string serialize(const model::TestCase&) const = 0;
	};

}}}
