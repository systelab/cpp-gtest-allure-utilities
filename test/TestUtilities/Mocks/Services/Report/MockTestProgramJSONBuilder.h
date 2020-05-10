#pragma once

#include "GTestAllureUtilities/Model/TestProgram.h"
#include "GTestAllureUtilities/Services/Report/ITestProgramJSONBuilder.h"


namespace systelab { namespace gtest_allure { namespace test_utility {

	class MockTestProgramJSONBuilder : public service::ITestProgramJSONBuilder
	{
	public:
		MockTestProgramJSONBuilder();
		virtual ~MockTestProgramJSONBuilder();

		MOCK_CONST_METHOD1(buildJSONFiles, void(const model::TestProgram&));
	};

}}}

