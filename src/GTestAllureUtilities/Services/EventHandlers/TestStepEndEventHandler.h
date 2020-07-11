#pragma once

#include "ITestStepEndEventHandler.h"

#include <memory>


namespace systelab { namespace gtest_allure { namespace model {
	class Action;
	class Step;
	class TestCase;
	class TestProgram;
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ITimeService;
	class IUUIDGeneratorService;

	class TestStepEndEventHandler : public ITestStepEndEventHandler
	{
	public:
		TestStepEndEventHandler(model::TestProgram&, std::unique_ptr<ITimeService>);
		virtual ~TestStepEndEventHandler() = default;

		void handleTestStepEnd(model::Status) const;

	private:
		model::Step& getRunningTestStep() const;
		model::TestCase& getRunningTestCase() const;
		model::TestSuite& getRunningTestSuite() const;

	private:
		model::TestProgram& m_testProgram;
		std::unique_ptr<ITimeService> m_timeService;
	};

}}}
