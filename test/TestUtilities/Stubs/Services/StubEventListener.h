#pragma once

#include "GTestAllureUtilities/Model/Status.h"
#include "GTestAllureUtilities/Services/IServicesFactory.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestCaseEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestCaseStartEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestProgramEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestProgramStartEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestSuiteEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestSuiteStartEventHandler.h"


namespace systelab { namespace gtest_allure { namespace test_utility {

	class StubEventListener
	{
	public:
		StubEventListener(service::IServicesFactory&);
		virtual ~StubEventListener() = default;

		void onProgramStart() const;
		void onTestSuiteStart(const std::string& testSuiteName) const;
		void onTestStart(const std::string& testCaseName) const;
		void onTestEnd(model::Status) const;
		void onTestSuiteEnd(model::Status) const;
		void onProgramEnd() const;

	private:
		service::IServicesFactory& m_servicesFactory;
		std::unique_ptr<service::ITestProgramStartEventHandler> m_testProgramStartEventHandler;
		std::unique_ptr<service::ITestSuiteStartEventHandler> m_testSuiteStartEventHandler;
		std::unique_ptr<service::ITestCaseStartEventHandler> m_testCaseStartEventHandler;
		std::unique_ptr<service::ITestCaseEndEventHandler> m_testCaseEndEventHandler;
		std::unique_ptr<service::ITestSuiteEndEventHandler> m_testSuiteEndEventHandler;
		std::unique_ptr<service::ITestProgramEndEventHandler> m_testProgramEndEventHandler;
	};

}}}

