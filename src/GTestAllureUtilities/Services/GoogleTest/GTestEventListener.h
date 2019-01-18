#pragma once

#include "Model/TestSuite.h"

#include <gtest/gtest.h>
#include <memory>


namespace systelab { namespace gtest_allure_utilities { namespace service {

	class ITestCaseEndEventHandler;
	class ITestCaseStartEventHandler;
	class ITestSuiteJSONBuilder;

	class GTestEventListener : public ::testing::EmptyTestEventListener
	{
	public:
		GTestEventListener(model::TestSuite&,
						   std::unique_ptr<ITestCaseStartEventHandler>,
						   std::unique_ptr<ITestCaseEndEventHandler>,
						   std::unique_ptr<ITestSuiteJSONBuilder>);
		virtual ~GTestEventListener() = default;

		virtual void OnTestProgramStart(const ::testing::UnitTest&);

		virtual void OnTestStart(const ::testing::TestInfo&);
		virtual void OnTestEnd(const ::testing::TestInfo&);

		virtual void OnTestProgramEnd(const ::testing::UnitTest&);

	private:
		model::TestSuite& m_testSuite;
		std::unique_ptr<ITestCaseStartEventHandler> m_testCaseStartEventHandler;
		std::unique_ptr<ITestCaseEndEventHandler> m_testCaseEndEventHandler;
		std::unique_ptr<ITestSuiteJSONBuilder> m_testSuiteJSONBuilder;
	};

}}}
