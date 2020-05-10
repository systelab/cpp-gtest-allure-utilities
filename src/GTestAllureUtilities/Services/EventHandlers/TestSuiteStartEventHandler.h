#pragma once

#include "ITestSuiteStartEventHandler.h"

#include <memory>


namespace systelab { namespace gtest_allure { namespace model {
	class TestProgram;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ITimeService;
	class IUUIDGeneratorService;

	class TestSuiteStartEventHandler : public ITestSuiteStartEventHandler
	{
	public:
		TestSuiteStartEventHandler(model::TestProgram&,
								   std::unique_ptr<IUUIDGeneratorService>,
								   std::unique_ptr<ITimeService>);
		virtual ~TestSuiteStartEventHandler() = default;

		void handleTestSuiteStart(const std::string& testSuiteName) const;

	private:
		model::TestProgram& m_testProgram;
		std::unique_ptr<IUUIDGeneratorService> m_uuidGeneratorService;
		std::unique_ptr<ITimeService> m_timeService;
	};

}}}
