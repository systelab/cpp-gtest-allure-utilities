#pragma once

#include "ITestCaseStartEventHandler.h"

#include <memory>


namespace systelab { namespace gtest_allure { namespace model {
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ITimeService;
	class IUUIDGeneratorService;

	class TestCaseStartEventHandler : public ITestCaseStartEventHandler
	{
	public:
		TestCaseStartEventHandler(model::TestSuite&,
								  std::unique_ptr<IUUIDGeneratorService>,
								  std::unique_ptr<ITimeService>);
		virtual ~TestCaseStartEventHandler() = default;

		void handleTestCaseStart(const std::string& testCaseName) const;

	private:
		model::TestSuite& m_testSuite;
		std::unique_ptr<IUUIDGeneratorService> m_uuidGeneratorService;
		std::unique_ptr<ITimeService> m_timeService;
	};

}}}
