#include "StubEventListener.h"

#include "GTestAllureUtilities/Services/EventHandlers/ITestProgramStartEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestCaseStartEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestCaseEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestProgramEndEventHandler.h"


using namespace testing;

namespace systelab { namespace gtest_allure_utilities { namespace test_utility {

	StubEventListener::StubEventListener(service::IServicesFactory& servicesFactory)
		:m_servicesFactory(servicesFactory)
	{
		m_testProgramStartEventHandler = m_servicesFactory.buildTestProgramStartEventHandler();
		m_testCaseStartEventHandler = m_servicesFactory.buildTestCaseStartEventHandler();
		m_testCaseEndEventHandler = m_servicesFactory.buildTestCaseEndEventHandler();
		m_testProgramEndEventHandler = m_servicesFactory.buildTestProgramEndEventHandler();
	}

	void StubEventListener::onProgramStart() const
	{
		m_testProgramStartEventHandler->handleTestProgramStart();
	}

	void StubEventListener::onTestStart(const std::string& testCaseName) const
	{
		m_testCaseStartEventHandler->handleTestCaseStart(testCaseName);
	}

	void StubEventListener::onTestEnd(model::Status status) const
	{
		m_testCaseEndEventHandler->handleTestCaseEnd(status);
	}

	void StubEventListener::onProgramEnd() const
	{
		m_testProgramEndEventHandler->handleTestProgramEnd();
	}

}}}

