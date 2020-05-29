#pragma once

#include "ITestStepStartEventHandler.h"

#include <memory>
#include <stdexcept>


namespace systelab { namespace gtest_allure { namespace model {
	class Step;
	class TestProgram;
	class TestSuite;
	class TestCase;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ITimeService;

	class TestStepStartEventHandler : public ITestStepStartEventHandler
	{
	public:
		TestStepStartEventHandler(model::TestProgram&,
								  std::unique_ptr<ITimeService>);
		virtual ~TestStepStartEventHandler() = default;

		void handleTestStepStart(const std::string& testStepDescription, bool isAction) const override;

	public:
		struct NoRunningTestSuiteException : std::runtime_error
		{
			NoRunningTestSuiteException()
				:std::runtime_error("No running test suite found when handling event for test step start")
			{}
		};

		struct NoRunningTestCaseException : std::runtime_error
		{
			NoRunningTestCaseException()
				:std::runtime_error("No running test case found when handling event for test step start")
			{}
		};

	private:
		std::unique_ptr<model::Step> buildStep(bool isAction) const;
		model::TestCase& getRunningTestCase() const;
		model::TestSuite& getRunningTestSuite() const;

	private:
		model::TestProgram& m_testProgram;
		std::unique_ptr<ITimeService> m_timeService;
	};

}}}
