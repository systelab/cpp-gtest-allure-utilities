#pragma once

#include "GTestAllureUtilities/Model/TestSuite.h"

#include <gtest/gtest.h>
#include <memory>


namespace systelab { namespace gtest_allure { namespace service {

	class ITestCaseEndEventHandler;
	class ITestCaseStartEventHandler;
	class ITestProgramEndEventHandler;
	class ITestProgramStartEventHandler;

	class GTestEventListener : public ::testing::EmptyTestEventListener
	{
	public:
		GTestEventListener(std::unique_ptr<ITestProgramStartEventHandler>,
						   std::unique_ptr<ITestCaseStartEventHandler>,
						   std::unique_ptr<ITestCaseEndEventHandler>,
						   std::unique_ptr<ITestProgramEndEventHandler>);
		virtual ~GTestEventListener() = default;

		virtual void OnTestProgramStart(const ::testing::UnitTest&);
		virtual void OnTestStart(const ::testing::TestInfo&);
		virtual void OnTestEnd(const ::testing::TestInfo&);
		virtual void OnTestProgramEnd(const ::testing::UnitTest&);

	private:
		std::unique_ptr<ITestProgramStartEventHandler> m_testProgramStartEventHandler;
		std::unique_ptr<ITestCaseStartEventHandler> m_testCaseStartEventHandler;
		std::unique_ptr<ITestCaseEndEventHandler> m_testCaseEndEventHandler;
		std::unique_ptr<ITestProgramEndEventHandler> m_testProgramEndEventHandler;
	};

}}}
