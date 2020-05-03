#pragma once

#include "IServicesFactory.h"


namespace systelab { namespace gtest_allure { namespace model {
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ServicesFactory : public IServicesFactory
	{
	public:
		ServicesFactory(model::TestSuite&);
		virtual ~ServicesFactory() = default;

		// GTest services
		virtual std::unique_ptr<::testing::TestEventListener> buildGTestEventListener() const;

		// Lifecycle events handling services
		virtual std::unique_ptr<ITestProgramStartEventHandler> buildTestProgramStartEventHandler() const;
		virtual std::unique_ptr<ITestCaseStartEventHandler> buildTestCaseStartEventHandler() const;
		virtual std::unique_ptr<ITestCaseEndEventHandler> buildTestCaseEndEventHandler() const;
		virtual std::unique_ptr<ITestProgramEndEventHandler> buildTestProgramEndEventHandler() const;

		// JSON services
		virtual std::unique_ptr<ITestSuiteJSONBuilder> buildTestSuiteJSONBuilder() const;
		virtual std::unique_ptr<ITestCaseJSONSerializer> buildTestCaseJSONSerializer() const;

		// System services
		virtual std::unique_ptr<IUUIDGeneratorService> buildUUIDGeneratorService() const;
		virtual std::unique_ptr<IFileService> buildFileService() const;
		virtual std::unique_ptr<ITimeService> buildTimeService() const;

	private:
		model::TestSuite& m_testSuite;
	};

}}}
