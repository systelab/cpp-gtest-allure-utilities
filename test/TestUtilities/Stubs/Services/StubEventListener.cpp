#include "stdafx.h"
#include "StubEventListener.h"


using namespace testing;

namespace systelab { namespace gtest_allure { namespace test_utility {

	StubEventListener::StubEventListener(service::IServicesFactory& servicesFactory)
		:m_servicesFactory(servicesFactory)
	{
		m_testProgramStartEventHandler = m_servicesFactory.buildTestProgramStartEventHandler();
		m_testSuiteStartEventHandler = m_servicesFactory.buildTestSuiteStartEventHandler();
		m_testCaseStartEventHandler = m_servicesFactory.buildTestCaseStartEventHandler();
		m_testCaseEndEventHandler = m_servicesFactory.buildTestCaseEndEventHandler();
		m_testSuiteEndEventHandler = m_servicesFactory.buildTestSuiteEndEventHandler();
		m_testProgramEndEventHandler = m_servicesFactory.buildTestProgramEndEventHandler();
	}

	void StubEventListener::onProgramStart() const
	{
		m_testProgramStartEventHandler->handleTestProgramStart();
	}

	void StubEventListener::onTestSuiteStart(const std::string& testSuiteName) const
	{
		m_testSuiteStartEventHandler->handleTestSuiteStart(testSuiteName);
	}

	void StubEventListener::onTestStart(const std::string& testCaseName) const
	{
		m_testCaseStartEventHandler->handleTestCaseStart(testCaseName);
	}

	void StubEventListener::onTestEnd(model::Status status) const
	{
		m_testCaseEndEventHandler->handleTestCaseEnd(status);
	}

	void StubEventListener::onTestSuiteEnd(model::Status status) const
	{
		m_testSuiteEndEventHandler->handleTestSuiteEnd(status);
	}

	void StubEventListener::onProgramEnd() const
	{
		m_testProgramEndEventHandler->handleTestProgramEnd();
	}

}}}

