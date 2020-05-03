#pragma once

#include "ITestCaseEndEventHandler.h"

#include <memory>


namespace systelab { namespace gtest_allure { namespace model {
	class TestCase;
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ITimeService;
	class IUUIDGeneratorService;

	class TestCaseEndEventHandler : public ITestCaseEndEventHandler
	{
	public:
		TestCaseEndEventHandler(model::TestSuite&,
								std::unique_ptr<ITimeService>);
		virtual ~TestCaseEndEventHandler() = default;

		void handleTestCaseEnd(model::Status) const;

	private:
		model::TestCase& getRunningTestCase() const;

	private:
		model::TestSuite& m_testSuite;
		std::unique_ptr<ITimeService> m_timeService;
	};

}}}
