#pragma once

#include "ITestCaseEndEventHandler.h"

#include <memory>


namespace systelab { namespace gtest_allure { namespace model {
	class Action;
	class TestCase;
	class TestProgram;
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ITimeService;
	class IUUIDGeneratorService;

	class TestCaseEndEventHandler : public ITestCaseEndEventHandler
	{
	public:
		TestCaseEndEventHandler(model::TestProgram&, std::unique_ptr<ITimeService>);
		virtual ~TestCaseEndEventHandler() = default;

		void handleTestCaseEnd(model::Status) const;

	private:
		model::Action& getRunningAction() const;
		model::TestCase& getRunningTestCase() const;
		model::TestSuite& getRunningTestSuite() const;

	private:
		model::TestProgram& m_testProgram;
		std::unique_ptr<ITimeService> m_timeService;
	};

}}}
