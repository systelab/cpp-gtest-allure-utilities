#pragma once

#include "GTestAllureUtilities/Model/TestSuite.h"
#include "TestUtilities/Mocks/Services/MockServicesFactory.h"


namespace systelab { namespace gtest_allure { namespace test_utility {

	class StubServicesFactory : public MockServicesFactory
	{
	public:
		StubServicesFactory(model::TestSuite&);
		virtual ~StubServicesFactory();

		// GTest services
		::testing::TestEventListener* buildGTestEventListenerStub() const;

		// Lifecycle events handling services
		service::ITestProgramStartEventHandler* buildTestProgramStartEventHandlerStub() const;
		service::ITestCaseStartEventHandler* buildTestCaseStartEventHandlerStub() const;
		service::ITestCaseEndEventHandler* buildTestCaseEndEventHandlerStub() const;
		service::ITestProgramEndEventHandler* buildTestProgramEndEventHandlerStub() const;

		// Report services
		service::ITestSuiteJSONBuilder* buildTestSuiteJSONBuilderStub() const;
		service::ITestCaseJSONSerializer* buildTestCaseJSONSerializerStub() const;

		// System services
		service::IUUIDGeneratorService* buildUUIDGeneratorServiceStub() const;
		service::IFileService* buildFileServiceStub() const;
		service::ITimeService* buildTimeServiceStub() const;

	private:
		model::TestSuite& m_testSuite;
	};

}}}

