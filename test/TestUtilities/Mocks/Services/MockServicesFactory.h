#pragma once

#include "GTestAllureUtilities/Services/IServicesFactory.h"


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

		std::unique_ptr<service::ITestSuiteStartEventHandler> buildTestSuiteStartEventHandler() const;
		MOCK_CONST_METHOD0(buildTestSuiteStartEventHandlerProxy, service::ITestSuiteStartEventHandler* ());

		std::unique_ptr<service::ITestCaseStartEventHandler> buildTestCaseStartEventHandler() const;
		MOCK_CONST_METHOD0(buildTestCaseStartEventHandlerProxy, service::ITestCaseStartEventHandler*());

		std::unique_ptr<service::ITestCaseEndEventHandler> buildTestCaseEndEventHandler() const;
		MOCK_CONST_METHOD0(buildTestCaseEndEventHandlerProxy, service::ITestCaseEndEventHandler*());

		std::unique_ptr<service::ITestSuiteEndEventHandler> buildTestSuiteEndEventHandler() const;
		MOCK_CONST_METHOD0(buildTestSuiteEndEventHandlerProxy, service::ITestSuiteEndEventHandler* ());

		std::unique_ptr<service::ITestProgramEndEventHandler> buildTestProgramEndEventHandler() const;
		MOCK_CONST_METHOD0(buildTestProgramEndEventHandlerProxy, service::ITestProgramEndEventHandler*());


		// JSON services
		std::unique_ptr<service::ITestProgramJSONBuilder> buildTestProgramJSONBuilder() const;
		MOCK_CONST_METHOD0(buildTestProgramJSONBuilderProxy, service::ITestProgramJSONBuilder*());

		std::unique_ptr<service::ITestSuiteJSONSerializer> buildTestSuiteJSONSerializer() const;
		MOCK_CONST_METHOD0(buildTestSuiteJSONSerializerProxy, service::ITestSuiteJSONSerializer*());


		// System services
		std::unique_ptr<service::IUUIDGeneratorService> buildUUIDGeneratorService() const;
		MOCK_CONST_METHOD0(buildUUIDGeneratorServiceProxy, service::IUUIDGeneratorService*());

		std::unique_ptr<service::IFileService> buildFileService() const;
		MOCK_CONST_METHOD0(buildFileServiceProxy, service::IFileService*());

		std::unique_ptr<service::ITimeService> buildTimeService() const;
		MOCK_CONST_METHOD0(buildTimeServiceProxy, service::ITimeService*());
	};

}}}

