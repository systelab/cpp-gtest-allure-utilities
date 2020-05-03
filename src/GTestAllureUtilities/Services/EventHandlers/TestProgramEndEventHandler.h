#pragma once

#include "ITestProgramEndEventHandler.h"

#include <memory>


namespace systelab { namespace gtest_allure { namespace model {
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ITestSuiteJSONBuilder;

	class TestProgramEndEventHandler : public ITestProgramEndEventHandler
	{
	public:
		TestProgramEndEventHandler(model::TestSuite&,
								   std::unique_ptr<ITestSuiteJSONBuilder>);
		virtual ~TestProgramEndEventHandler() = default;

		void handleTestProgramEnd() const;

	private:
		model::TestSuite& m_testSuite;
		std::unique_ptr<ITestSuiteJSONBuilder> m_testSuiteJSONBuilderService;
	};

}}}
