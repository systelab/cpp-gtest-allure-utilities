#pragma once

#include <gtest/gtest.h>
#include <memory>


namespace systelab { namespace gtest_allure_utilities { namespace service {

	class IFileService;
	class ITestCaseJSONSerializer;
	class ITestCaseStartEventHandler;
	class ITestCaseEndEventHandler;
	class ITestSuiteJSONBuilder;
	class IUUIDGeneratorService;

	class IServicesFactory
	{
	public:
		virtual ~IServicesFactory() = default;

		// GTest services
		virtual std::unique_ptr<::testing::TestEventListener> buildGTestEventListener() const = 0;

		// Lifecycle events handling services
		virtual std::unique_ptr<ITestCaseStartEventHandler> buildTestCaseStartEventHandler() const = 0;
		virtual std::unique_ptr<ITestCaseEndEventHandler> buildTestCaseEndEventHandler() const = 0;

		// JSON services
		virtual std::unique_ptr<ITestSuiteJSONBuilder> buildTestSuiteJSONBuilder() const = 0;
		virtual std::unique_ptr<ITestCaseJSONSerializer> buildTestCaseJSONSerializer() const = 0;

		// System services
		virtual std::unique_ptr<IUUIDGeneratorService> buildUUIDGeneratorService() const = 0;
		virtual std::unique_ptr<IFileService> buildFileService() const = 0;
	};

}}}
