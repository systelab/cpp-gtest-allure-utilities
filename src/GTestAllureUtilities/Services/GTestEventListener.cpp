#include "GTestEventListener.h"

#include "Services/ITestCaseStartEventHandler.h"
#include "Services/ITestSuiteJSONBuilder.h"


namespace systelab { namespace gtest_allure_utilities { namespace service {

	GTestEventListener::GTestEventListener(model::TestSuite& testSuite,
										   std::unique_ptr<service::ITestCaseStartEventHandler> testCaseStartEventHandler,
										   std::unique_ptr<service::ITestSuiteJSONBuilder> testSuiteJSONBuilder)
		:m_testSuite(testSuite)
		,m_testCaseStartEventHandler(std::move(testCaseStartEventHandler))
		,m_testSuiteJSONBuilder(std::move(testSuiteJSONBuilder))
	{
	}

	void GTestEventListener::OnTestProgramStart(const ::testing::UnitTest&)
	{
	}

	void GTestEventListener::OnTestStart(const ::testing::TestInfo& testInfo)
	{
		std::string testCaseName = std::string(testInfo.test_case_name()) + "." + testInfo.name();
		m_testCaseStartEventHandler->handleTestCaseStart(testCaseName);
	}

	void GTestEventListener::OnTestEnd(const ::testing::TestInfo&)
	{
	}

	void GTestEventListener::OnTestProgramEnd(const ::testing::UnitTest&)
	{
		m_testSuiteJSONBuilder->buildJSONFiles(m_testSuite);
	}

}}}
