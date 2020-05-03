#include "TestProgramEndEventHandler.h"

#include "Model/TestSuite.h"
#include "Services/Report/ITestSuiteJSONBuilder.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestProgramEndEventHandler::TestProgramEndEventHandler(model::TestSuite& testSuite,
														   std::unique_ptr<ITestSuiteJSONBuilder> testSuiteJSONBuilderService)
		:m_testSuite(testSuite)
		,m_testSuiteJSONBuilderService(std::move(testSuiteJSONBuilderService))
	{
	}

	void TestProgramEndEventHandler::handleTestProgramEnd() const
	{
		m_testSuiteJSONBuilderService->buildJSONFiles(m_testSuite);
	}

}}}
