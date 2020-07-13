#pragma once

#include <gtest/gtest.h>
#include <memory>


namespace systelab { namespace gtest_allure { namespace service {

	class IFileService;
	class IGTestStatusChecker;
	class ITestCaseEndEventHandler;
	class ITestCaseStartEventHandler;
	class ITestProgramEndEventHandler;
	class ITestProgramStartEventHandler;
	class ITestProgramJSONBuilder;
	class ITestStepEndEventHandler;
	class ITestStepStartEventHandler;
	class ITestSuiteJSONSerializer;
	class ITestSuiteStartEventHandler;
	class ITestSuiteEndEventHandler;
	class ITestSuitePropertySetter;
	class ITimeService;
	class IUUIDGeneratorService;

	class IServicesFactory
	{
	public:
		virtual ~IServicesFactory() = default;

		// GTest services
		virtual std::unique_ptr<::testing::TestEventListener> buildGTestEventListener() const = 0;
		virtual std::unique_ptr<IGTestStatusChecker> buildGTestStatusChecker() const = 0;

		// Lifecycle events handling services
		virtual std::unique_ptr<ITestProgramStartEventHandler> buildTestProgramStartEventHandler() const = 0;
		virtual std::unique_ptr<ITestSuiteStartEventHandler> buildTestSuiteStartEventHandler() const = 0;
		virtual std::unique_ptr<ITestCaseStartEventHandler> buildTestCaseStartEventHandler() const = 0;
		virtual std::unique_ptr<ITestStepStartEventHandler> buildTestStepStartEventHandler() const = 0;
		virtual std::unique_ptr<ITestStepEndEventHandler> buildTestStepEndEventHandler() const = 0;
		virtual std::unique_ptr<ITestCaseEndEventHandler> buildTestCaseEndEventHandler() const = 0;
		virtual std::unique_ptr<ITestSuiteEndEventHandler> buildTestSuiteEndEventHandler() const = 0;
		virtual std::unique_ptr<ITestProgramEndEventHandler> buildTestProgramEndEventHandler() const = 0;

		// Property services
		virtual std::unique_ptr<ITestSuitePropertySetter> buildTestSuitePropertySetter() const = 0;

		// JSON services
		virtual std::unique_ptr<ITestProgramJSONBuilder> buildTestProgramJSONBuilder() const = 0;
		virtual std::unique_ptr<ITestSuiteJSONSerializer> buildTestSuiteJSONSerializer() const = 0;

		// System services
		virtual std::unique_ptr<IUUIDGeneratorService> buildUUIDGeneratorService() const = 0;
		virtual std::unique_ptr<IFileService> buildFileService() const = 0;
		virtual std::unique_ptr<ITimeService> buildTimeService() const = 0;
	};

}}}
