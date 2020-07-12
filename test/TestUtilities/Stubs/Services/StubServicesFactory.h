#pragma once

#include "GTestAllureUtilities/Model/TestProgram.h"
#include "TestUtilities/Mocks/Services/MockServicesFactory.h"


namespace systelab { namespace gtest_allure { namespace test_utility {

	class StubServicesFactory : public MockServicesFactory
	{
	public:
		StubServicesFactory(model::TestProgram&);
		virtual ~StubServicesFactory();

		// GTest services
		::testing::TestEventListener* buildGTestEventListenerStub() const;
		service::IGTestStatusChecker* buildGTestStatusCheckerStub() const;

		// Lifecycle events handling services
		service::ITestProgramStartEventHandler* buildTestProgramStartEventHandlerStub() const;
		service::ITestSuiteStartEventHandler* buildTestSuiteStartEventHandlerStub() const;
		service::ITestCaseStartEventHandler* buildTestCaseStartEventHandlerStub() const;
		service::ITestStepStartEventHandler* buildTestStepStartEventHandlerStub() const;
		service::ITestStepEndEventHandler* buildTestStepEndEventHandlerStub() const;
		service::ITestCaseEndEventHandler* buildTestCaseEndEventHandlerStub() const;
		service::ITestSuiteEndEventHandler* buildTestSuiteEndEventHandlerStub() const;
		service::ITestProgramEndEventHandler* buildTestProgramEndEventHandlerStub() const;

		// Report services
		service::ITestProgramJSONBuilder* buildTestProgramJSONBuilderStub() const;
		service::ITestSuiteJSONSerializer* buildTestSuiteJSONSerializerStub() const;

		// System services
		service::IUUIDGeneratorService* buildUUIDGeneratorServiceStub() const;
		service::IFileService* buildFileServiceStub() const;
		service::ITimeService* buildTimeServiceStub() const;

	private:
		model::TestProgram& m_testProgram;
	};

}}}

