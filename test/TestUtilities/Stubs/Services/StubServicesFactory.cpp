#include "StubServicesFactory.h"

#include "GTestAllureUtilities/Model/TestSuite.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestCaseEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestCaseStartEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestProgramEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestProgramStartEventHandler.h"
#include "GTestAllureUtilities/Services/GoogleTest/GTestEventListener.h"
#include "GTestAllureUtilities/Services/System/FileService.h"
#include "GTestAllureUtilities/Services/System/TimeService.h"
#include "GTestAllureUtilities/Services/System/UUIDGeneratorService.h"
#include "GTestAllureUtilities/Services/Report/TestCaseJSONSerializer.h"
#include "GTestAllureUtilities/Services/Report/TestSuiteJSONBuilder.h"


using namespace testing;

namespace systelab { namespace gtest_allure_utilities { namespace test_utility {

	StubServicesFactory::StubServicesFactory(model::TestSuite& testSuite)
		:m_testSuite(testSuite)
	{
		ON_CALL(*this, buildGTestEventListenerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildGTestEventListenerStub));

		ON_CALL(*this, buildTestProgramStartEventHandlerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestProgramStartEventHandlerStub));
		ON_CALL(*this, buildTestCaseStartEventHandlerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestCaseStartEventHandlerStub));
		ON_CALL(*this, buildTestCaseEndEventHandlerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestCaseEndEventHandlerStub));
		ON_CALL(*this, buildTestProgramEndEventHandlerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestProgramEndEventHandlerStub));

		ON_CALL(*this, buildTestSuiteJSONBuilderProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestSuiteJSONBuilderStub));
		ON_CALL(*this, buildTestCaseJSONSerializerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestCaseJSONSerializerStub));

		ON_CALL(*this, buildUUIDGeneratorServiceProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildUUIDGeneratorServiceStub));
		ON_CALL(*this, buildFileServiceProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildFileServiceStub));
		ON_CALL(*this, buildTimeServiceProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTimeServiceStub));
	}

	StubServicesFactory::~StubServicesFactory()
	{
	}


	// GTest services
	::testing::TestEventListener* StubServicesFactory::buildGTestEventListenerStub() const
	{
		auto testProgramStartEventHandler = buildTestProgramStartEventHandler();
		auto testCaseStartEventHandler = buildTestCaseStartEventHandler();
		auto testCaseEndEventHandler = buildTestCaseEndEventHandler();
		auto testProgramEndEventHandler = buildTestProgramEndEventHandler();
		return new service::GTestEventListener
						(std::move(testProgramStartEventHandler), std::move(testCaseStartEventHandler),
						 std::move(testCaseEndEventHandler), std::move(testProgramEndEventHandler));
	}


	// Lifecycle events handling services
	service::ITestProgramStartEventHandler* StubServicesFactory::buildTestProgramStartEventHandlerStub() const
	{
		return new service::TestProgramStartEventHandler(m_testSuite);
	}

	service::ITestCaseStartEventHandler* StubServicesFactory::buildTestCaseStartEventHandlerStub() const
	{
		auto timeService = buildTimeService();
		auto uuidGeneratorService = buildUUIDGeneratorService();
		return new service::TestCaseStartEventHandler(m_testSuite, std::move(uuidGeneratorService), std::move(timeService));
	}

	service::ITestCaseEndEventHandler* StubServicesFactory::buildTestCaseEndEventHandlerStub() const
	{
		auto timeService = buildTimeService();
		return new service::TestCaseEndEventHandler(m_testSuite, std::move(timeService));
	}

	service::ITestProgramEndEventHandler* StubServicesFactory::buildTestProgramEndEventHandlerStub() const
	{
		auto testSuiteJSONBuilder = buildTestSuiteJSONBuilder();
		return new service::TestProgramEndEventHandler(m_testSuite, std::move(testSuiteJSONBuilder));
	}


	// Report services
	service::ITestSuiteJSONBuilder* StubServicesFactory::buildTestSuiteJSONBuilderStub() const
	{
		auto fileService = buildFileService();
		auto testCaseJSONSerializer = buildTestCaseJSONSerializer();
		return new service::TestSuiteJSONBuilder(std::move(testCaseJSONSerializer), std::move(fileService));
	}

	service::ITestCaseJSONSerializer* StubServicesFactory::buildTestCaseJSONSerializerStub() const
	{
		return new service::TestCaseJSONSerializer();
	}


	// System services
	service::IUUIDGeneratorService* StubServicesFactory::buildUUIDGeneratorServiceStub() const
	{
		return new service::UUIDGeneratorService();
	}

	service::IFileService* StubServicesFactory::buildFileServiceStub() const
	{
		return new service::FileService();
	}

	service::ITimeService* StubServicesFactory::buildTimeServiceStub() const
	{
		return new service::TimeService();
	}

}}}

