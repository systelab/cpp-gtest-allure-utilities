#pragma once

#include "GTestAllureUtilities/Model/Status.h"
#include "GTestAllureUtilities/Services/IServicesFactory.h"


namespace systelab { namespace gtest_allure_utilities { namespace test_utility {

	class StubEventListener
	{
	public:
		StubEventListener(service::IServicesFactory&);
		virtual ~StubEventListener() = default;

		void onProgramStart() const;
		void onTestStart(const std::string& testCaseName) const;
		void onTestEnd(model::Status) const;
		void onProgramEnd() const;

	private:
		service::IServicesFactory& m_servicesFactory;
		std::unique_ptr<service::ITestProgramStartEventHandler> m_testProgramStartEventHandler;
		std::unique_ptr<service::ITestCaseStartEventHandler> m_testCaseStartEventHandler;
		std::unique_ptr<service::ITestCaseEndEventHandler> m_testCaseEndEventHandler;
		std::unique_ptr<service::ITestProgramEndEventHandler> m_testProgramEndEventHandler;
	};

}}}

