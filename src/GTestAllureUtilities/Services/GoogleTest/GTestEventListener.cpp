#include "GTestEventListener.h"

#include "Services/EventHandlers/ITestCaseEndEventHandler.h"
#include "Services/EventHandlers/ITestCaseStartEventHandler.h"
#include "Services/EventHandlers/ITestSuiteStartEventHandler.h"
#include "Services/EventHandlers/ITestSuiteEndEventHandler.h"
#include "Services/EventHandlers/ITestProgramEndEventHandler.h"
#include "Services/EventHandlers/ITestProgramStartEventHandler.h"


namespace systelab { namespace gtest_allure { namespace service {

	GTestEventListener::GTestEventListener(std::unique_ptr<service::ITestProgramStartEventHandler> testProgramStartEventHandler,
										   std::unique_ptr<service::ITestSuiteStartEventHandler> testSuiteStartEventHandler,
										   std::unique_ptr<service::ITestCaseStartEventHandler> testCaseStartEventHandler,
										   std::unique_ptr<service::ITestCaseEndEventHandler> testCaseEndEventHandler,
										   std::unique_ptr<service::ITestSuiteEndEventHandler> testSuiteEndEventHandler,
										   std::unique_ptr<service::ITestProgramEndEventHandler> testProgramEndEventHandler)
		:m_testProgramStartEventHandler(std::move(testProgramStartEventHandler))
		,m_testSuiteStartEventHandler(std::move(testSuiteStartEventHandler))
		,m_testCaseStartEventHandler(std::move(testCaseStartEventHandler))
		,m_testCaseEndEventHandler(std::move(testCaseEndEventHandler))
		,m_testSuiteEndEventHandler(std::move(testSuiteEndEventHandler))
		,m_testProgramEndEventHandler(std::move(testProgramEndEventHandler))
	{
	}

	void GTestEventListener::OnTestProgramStart(const ::testing::UnitTest&)
	{
		m_testProgramStartEventHandler->handleTestProgramStart();
	}

	void GTestEventListener::OnTestSuiteStart(const ::testing::TestSuite& testSuiteInfo)
	{
		std::string testSuiteName = testSuiteInfo.name();
		m_testSuiteStartEventHandler->handleTestSuiteStart(testSuiteName);
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

	void GTestEventListener::OnTestSuiteEnd(const ::testing::TestSuite& testSuiteInfo)
	{
		model::Status status = testSuiteInfo.Passed() ? model::Status::PASSED : model::Status::FAILED;
		m_testSuiteEndEventHandler->handleTestSuiteEnd(status);
	}

	void GTestEventListener::OnTestProgramEnd(const ::testing::UnitTest&)
	{
		m_testProgramEndEventHandler->handleTestProgramEnd();
	}

}}}
