#pragma once

#include "GTestAllureUtilities/Services/IServicesFactory.h"

#include <gmock/gmock.h>


namespace systelab { namespace gtest_allure { namespace test_utility {

	class MockServicesFactory : public service::IServicesFactory
	{
	public:
		MockServicesFactory();
		virtual ~MockServicesFactory();

		// GTest services
		std::unique_ptr<::testing::TestEventListener> buildGTestEventListener() const;
		MOCK_CONST_METHOD0(buildGTestEventListenerProxy, ::testing::TestEventListener*());


		// Lifecycle events handling services
		std::unique_ptr<service::ITestProgramStartEventHandler> buildTestProgramStartEventHandler() const;
		MOCK_CONST_METHOD0(buildTestProgramStartEventHandlerProxy, service::ITestProgramStartEventHandler*());

		std::unique_ptr<service::ITestCaseStartEventHandler> buildTestCaseStartEventHandler() const;
		MOCK_CONST_METHOD0(buildTestCaseStartEventHandlerProxy, service::ITestCaseStartEventHandler*());

		std::unique_ptr<service::ITestCaseEndEventHandler> buildTestCaseEndEventHandler() const;
		MOCK_CONST_METHOD0(buildTestCaseEndEventHandlerProxy, service::ITestCaseEndEventHandler*());

		std::unique_ptr<service::ITestProgramEndEventHandler> buildTestProgramEndEventHandler() const;
		MOCK_CONST_METHOD0(buildTestProgramEndEventHandlerProxy, service::ITestProgramEndEventHandler*());


		// JSON services
		std::unique_ptr<service::ITestSuiteJSONBuilder> buildTestSuiteJSONBuilder() const;
		MOCK_CONST_METHOD0(buildTestSuiteJSONBuilderProxy, service::ITestSuiteJSONBuilder*());

		std::unique_ptr<service::ITestCaseJSONSerializer> buildTestCaseJSONSerializer() const;
		MOCK_CONST_METHOD0(buildTestCaseJSONSerializerProxy, service::ITestCaseJSONSerializer*());


		// System services
		std::unique_ptr<service::IUUIDGeneratorService> buildUUIDGeneratorService() const;
		MOCK_CONST_METHOD0(buildUUIDGeneratorServiceProxy, service::IUUIDGeneratorService*());

		std::unique_ptr<service::IFileService> buildFileService() const;
		MOCK_CONST_METHOD0(buildFileServiceProxy, service::IFileService*());

		std::unique_ptr<service::ITimeService> buildTimeService() const;
		MOCK_CONST_METHOD0(buildTimeServiceProxy, service::ITimeService*());
	};

}}}

