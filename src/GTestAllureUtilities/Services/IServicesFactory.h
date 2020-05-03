#pragma once

#include <gtest/gtest.h>
#include <memory>


namespace systelab { namespace gtest_allure { namespace service {

	class IFileService;
	class ITestCaseEndEventHandler;
	class ITestCaseJSONSerializer;
	class ITestCaseStartEventHandler;
	class ITestProgramEndEventHandler;
	class ITestProgramStartEventHandler;
	class ITestSuiteJSONBuilder;
	class ITimeService;
	class IUUIDGeneratorService;

	class IServicesFactory
	{
	public:
		virtual ~IServicesFactory() = default;

		// GTest services
		virtual std::unique_ptr<::testing::TestEventListener> buildGTestEventListener() const = 0;

		// Lifecycle events handling services
		virtual std::unique_ptr<ITestProgramStartEventHandler> buildTestProgramStartEventHandler() const = 0;
		virtual std::unique_ptr<ITestCaseStartEventHandler> buildTestCaseStartEventHandler() const = 0;
		virtual std::unique_ptr<ITestCaseEndEventHandler> buildTestCaseEndEventHandler() const = 0;
		virtual std::unique_ptr<ITestProgramEndEventHandler> buildTestProgramEndEventHandler() const = 0;

		// JSON services
		virtual std::unique_ptr<ITestSuiteJSONBuilder> buildTestSuiteJSONBuilder() const = 0;
		virtual std::unique_ptr<ITestCaseJSONSerializer> buildTestCaseJSONSerializer() const = 0;

		// System services
		virtual std::unique_ptr<IUUIDGeneratorService> buildUUIDGeneratorService() const = 0;
		virtual std::unique_ptr<IFileService> buildFileService() const = 0;
		virtual std::unique_ptr<ITimeService> buildTimeService() const = 0;
	};

}}}
