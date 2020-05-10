#pragma once

#include "ITestCaseStartEventHandler.h"

#include <memory>
#include <stdexcept>


namespace systelab { namespace gtest_allure { namespace model {
	class TestProgram;
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ITimeService;

	class TestCaseStartEventHandler : public ITestCaseStartEventHandler
	{
	public:
		TestCaseStartEventHandler(model::TestProgram&,
								  std::unique_ptr<ITimeService>);
		virtual ~TestCaseStartEventHandler() = default;

		void handleTestCaseStart(const std::string& testCaseName) const;

	public:
		struct NoRunningTestSuiteException : std::runtime_error
		{
			NoRunningTestSuiteException()
				:std::runtime_error("No running test suite found when handling event for test case start")
			{}
		};

	private:
		model::TestSuite& getRunningTestSuite() const;

	private:
		model::TestProgram& m_testProgram;
		std::unique_ptr<ITimeService> m_timeService;
	};

}}}
