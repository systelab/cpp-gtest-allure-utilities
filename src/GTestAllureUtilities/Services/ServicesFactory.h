#pragma once

#include "IServicesFactory.h"


namespace systelab { namespace gtest_allure { namespace model {
	class TestProgram;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ServicesFactory : public IServicesFactory
	{
	public:
		ServicesFactory(model::TestProgram&);
		virtual ~ServicesFactory() = default;

		// GTest services
		std::unique_ptr<::testing::TestEventListener> buildGTestEventListener() const override;
		std::unique_ptr<IGTestStatusChecker> buildGTestStatusChecker() const override;

		// Lifecycle events handling services
		std::unique_ptr<ITestProgramStartEventHandler> buildTestProgramStartEventHandler() const override;
		std::unique_ptr<ITestSuiteStartEventHandler> buildTestSuiteStartEventHandler() const override;
		std::unique_ptr<ITestCaseStartEventHandler> buildTestCaseStartEventHandler() const override;
		std::unique_ptr<ITestStepStartEventHandler> buildTestStepStartEventHandler() const override;
		std::unique_ptr<ITestStepEndEventHandler> buildTestStepEndEventHandler() const override;
		std::unique_ptr<ITestCaseEndEventHandler> buildTestCaseEndEventHandler() const override;
		std::unique_ptr<ITestSuiteEndEventHandler> buildTestSuiteEndEventHandler() const override;
		std::unique_ptr<ITestProgramEndEventHandler> buildTestProgramEndEventHandler() const override;

		// Property services
		std::unique_ptr<ITestSuitePropertySetter> buildTestSuitePropertySetter() const override;
		std::unique_ptr<ITestCasePropertySetter> buildTestCasePropertySetter() const override;

		// JSON services
		std::unique_ptr<ITestProgramJSONBuilder> buildTestProgramJSONBuilder() const override;
		std::unique_ptr<ITestSuiteJSONSerializer> buildTestSuiteJSONSerializer() const override;

		// System services
		std::unique_ptr<IUUIDGeneratorService> buildUUIDGeneratorService() const override;
		std::unique_ptr<IFileService> buildFileService() const override;
		std::unique_ptr<ITimeService> buildTimeService() const override;

		// Unique instance (to be used by integration tests)
		static IServicesFactory* getInstance();
		static void setInstance(std::unique_ptr<IServicesFactory>);

	private:
		model::TestProgram& m_testProgram;
		static std::unique_ptr<IServicesFactory> m_instance;
	};

}}}
