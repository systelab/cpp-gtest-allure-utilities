#pragma once

#include "ITestCaseStartEventHandler.h"

#include <memory>


namespace systelab { namespace gtest_allure_utilities { namespace model {
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure_utilities { namespace service {

	class IUUIDGeneratorService;

	class TestCaseStartEventHandler : public ITestCaseStartEventHandler
	{
	public:
		TestCaseStartEventHandler(model::TestSuite&,
								  std::unique_ptr<IUUIDGeneratorService>);
		virtual ~TestCaseStartEventHandler() = default;

		void handleTestCaseStart(const std::string& testCaseName) const;

	private:
		model::TestSuite& m_testSuite;
		std::unique_ptr<IUUIDGeneratorService> m_uuidGeneratorService;
	};

}}}
