#pragma once

#include "ITestProgramJSONBuilder.h"

#include <memory>


namespace systelab { namespace gtest_allure { namespace service {

	class IFileService;
	class ITestSuiteJSONSerializer;

	class TestProgramJSONBuilder : public ITestProgramJSONBuilder
	{
	public:
		TestProgramJSONBuilder(std::unique_ptr<ITestSuiteJSONSerializer>,
							   std::unique_ptr<IFileService>);
		virtual ~TestProgramJSONBuilder() = default;

		virtual void buildJSONFiles(const model::TestProgram&) const;

	private:
		std::unique_ptr<ITestSuiteJSONSerializer> m_testSuiteJSONSerializer;
		std::unique_ptr<IFileService> m_fileService;
	};

}}}
