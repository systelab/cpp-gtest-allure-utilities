#pragma once

#include <string>

namespace systelab { namespace gtest_allure { namespace model {
	class TestProgram;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ITestProgramJSONBuilder
	{
	public:
		virtual ~ITestProgramJSONBuilder() = default;

		virtual void buildJSONFiles(const model::TestProgram&) const = 0;
	};

}}}
