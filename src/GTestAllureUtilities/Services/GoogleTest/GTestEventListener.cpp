#include "GTestEventListener.h"

#include "Services/EventHandlers/ITestCaseEndEventHandler.h"
#include "Services/EventHandlers/ITestCaseStartEventHandler.h"
#include "Services/Report/ITestSuiteJSONBuilder.h"


namespace systelab { namespace gtest_allure_utilities { namespace service {

	GTestEventListener::GTestEventListener(model::TestSuite& testSuite,
										   std::unique_ptr<service::ITestCaseStartEventHandler> testCaseStartEventHandler,
										   std::unique_ptr<service::ITestCaseEndEventHandler> testCaseEndEventHandler,
										   std::unique_ptr<service::ITestSuiteJSONBuilder> testSuiteJSONBuilder)
		:m_testSuite(testSuite)
		,m_testCaseStartEventHandler(std::move(testCaseStartEventHandler))
		,m_testCaseEndEventHandler(std::move(testCaseEndEventHandler))
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

	void GTestEventListener::OnTestEnd(const ::testing::TestInfo& testInfo)
	{
		model::Status status = testInfo.result()->Passed() ? model::Status::PASSED : model::Status::FAILED;
		m_testCaseEndEventHandler->handleTestCaseEnd(status);
	}

	void GTestEventListener::OnTestProgramEnd(const ::testing::UnitTest&)
	{
		m_testSuiteJSONBuilder->buildJSONFiles(m_testSuite);
	}

}}}
