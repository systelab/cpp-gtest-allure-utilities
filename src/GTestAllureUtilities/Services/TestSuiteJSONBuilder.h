#pragma once

#include "ITestSuiteJSONBuilder.h"

#include <memory>


namespace systelab { namespace gtest_allure_utilities { namespace model {
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure_utilities { namespace service {

	class IFileService;
	class ITestCaseJSONSerializer;

	class TestSuiteJSONBuilder : public ITestSuiteJSONBuilder
	{
	public:
		TestSuiteJSONBuilder(std::unique_ptr<ITestCaseJSONSerializer>,
							 std::unique_ptr<IFileService>);
		virtual ~TestSuiteJSONBuilder() = default;

		virtual void buildJSONFiles(const model::TestSuite&) const;

	private:
		std::unique_ptr<ITestCaseJSONSerializer> m_testCaseJSONSerializer;
		std::unique_ptr<IFileService> m_fileService;
	};

}}}
