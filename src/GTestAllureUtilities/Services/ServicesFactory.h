#pragma once

#include "IServicesFactory.h"


namespace systelab { namespace gtest_allure_utilities { namespace model {
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure_utilities { namespace service {

	class ServicesFactory : public IServicesFactory
	{
	public:
		ServicesFactory(model::TestSuite&);
		virtual ~ServicesFactory() = default;

		// GTest services
		std::unique_ptr<::testing::TestEventListener> buildGTestEventListener() const;

		// Lifecycle events handling services
		std::unique_ptr<ITestCaseStartEventHandler> buildTestCaseStartEventHandler() const;
		std::unique_ptr<ITestCaseEndEventHandler> buildTestCaseEndEventHandler() const;

		// JSON services
		std::unique_ptr<ITestSuiteJSONBuilder> buildTestSuiteJSONBuilder() const;
		std::unique_ptr<ITestCaseJSONSerializer> buildTestCaseJSONSerializer() const;

		// System services
		std::unique_ptr<IUUIDGeneratorService> buildUUIDGeneratorService() const;
		std::unique_ptr<IFileService> buildFileService() const;
		std::unique_ptr<ITimeService> buildTimeService() const;

	private:
		model::TestSuite& m_testSuite;
	};

}}}
