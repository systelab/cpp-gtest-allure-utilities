#include "stdafx.h"
#include "StubServicesFactory.h"

#include "GTestAllureUtilities/Model/TestProgram.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestCaseEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestCaseStartEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestProgramEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestProgramStartEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestStepEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestStepStartEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestSuiteEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestSuiteStartEventHandler.h"
#include "GTestAllureUtilities/Services/GoogleTest/GTestEventListener.h"
#include "GTestAllureUtilities/Services/GoogleTest/GTestStatusChecker.h"
#include "GTestAllureUtilities/Services/Property/TestCasePropertySetter.h"
#include "GTestAllureUtilities/Services/Property/TestSuitePropertySetter.h"
#include "GTestAllureUtilities/Services/Report/TestSuiteJSONSerializer.h"
#include "GTestAllureUtilities/Services/Report/TestProgramJSONBuilder.h"
#include "GTestAllureUtilities/Services/System/FileService.h"
#include "GTestAllureUtilities/Services/System/TimeService.h"
#include "GTestAllureUtilities/Services/System/UUIDGeneratorService.h"

#include "RapidJSONAdapter/JSONAdapter.h"


using namespace testing;

namespace systelab { namespace gtest_allure { namespace test_utility {

	StubServicesFactory::StubServicesFactory(model::TestProgram& testProgram)
		:m_testProgram(testProgram)
	{
		ON_CALL(*this, buildGTestEventListenerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildGTestEventListenerStub));
		ON_CALL(*this, buildGTestStatusCheckerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildGTestStatusCheckerStub));

		ON_CALL(*this, buildTestProgramStartEventHandlerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestProgramStartEventHandlerStub));
		ON_CALL(*this, buildTestSuiteStartEventHandlerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestSuiteStartEventHandlerStub));
		ON_CALL(*this, buildTestCaseStartEventHandlerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestCaseStartEventHandlerStub));
		ON_CALL(*this, buildTestStepStartEventHandlerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestStepStartEventHandlerStub));
		ON_CALL(*this, buildTestStepEndEventHandlerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestStepEndEventHandlerStub));
		ON_CALL(*this, buildTestCaseEndEventHandlerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestCaseEndEventHandlerStub));
		ON_CALL(*this, buildTestSuiteEndEventHandlerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestSuiteEndEventHandlerStub));
		ON_CALL(*this, buildTestProgramEndEventHandlerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestProgramEndEventHandlerStub));

		ON_CALL(*this, buildTestSuitePropertySetterProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestSuitePropertySetterStub));
		ON_CALL(*this, buildTestCasePropertySetterProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestCasePropertySetterStub));

		ON_CALL(*this, buildTestProgramJSONBuilderProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestProgramJSONBuilderStub));
		ON_CALL(*this, buildTestSuiteJSONSerializerProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTestSuiteJSONSerializerStub));

		ON_CALL(*this, buildUUIDGeneratorServiceProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildUUIDGeneratorServiceStub));
		ON_CALL(*this, buildFileServiceProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildFileServiceStub));
		ON_CALL(*this, buildTimeServiceProxy()).WillByDefault(Invoke(this, &StubServicesFactory::buildTimeServiceStub));
	}

	StubServicesFactory::~StubServicesFactory() = default;


	// GTest services
	::testing::TestEventListener* StubServicesFactory::buildGTestEventListenerStub() const
	{
		auto testProgramStartEventHandler = buildTestProgramStartEventHandler();
		auto testSuiteStartEventHandler = buildTestSuiteStartEventHandler();
		auto testCaseStartEventHandler = buildTestCaseStartEventHandler();
		auto testCaseEndEventHandler = buildTestCaseEndEventHandler();
		auto testSuiteEndEventHandler = buildTestSuiteEndEventHandler();
		auto testProgramEndEventHandler = buildTestProgramEndEventHandler();

		return new service::GTestEventListener
						(std::move(testProgramStartEventHandler), std::move(testSuiteStartEventHandler),
						 std::move(testCaseStartEventHandler), std::move(testCaseEndEventHandler),
						 std::move(testSuiteEndEventHandler), std::move(testProgramEndEventHandler));
	}

	service::IGTestStatusChecker* StubServicesFactory::buildGTestStatusCheckerStub() const
	{
		return new service::GTestStatusChecker();
	}

	// Lifecycle events handling services
	service::ITestProgramStartEventHandler* StubServicesFactory::buildTestProgramStartEventHandlerStub() const
	{
		return new service::TestProgramStartEventHandler(m_testProgram);
	}

	service::ITestSuiteStartEventHandler* StubServicesFactory::buildTestSuiteStartEventHandlerStub() const
	{
		auto uuidGeneratorService = buildUUIDGeneratorService();
		auto timeService = buildTimeService();
		return new service::TestSuiteStartEventHandler(m_testProgram, std::move(uuidGeneratorService), std::move(timeService));
	}

	service::ITestCaseStartEventHandler* StubServicesFactory::buildTestCaseStartEventHandlerStub() const
	{
		auto timeService = buildTimeService();
		return new service::TestCaseStartEventHandler(m_testProgram, std::move(timeService));
	}

	service::ITestStepStartEventHandler* StubServicesFactory::buildTestStepStartEventHandlerStub() const
	{
		auto timeService = buildTimeService();
		return new service::TestStepStartEventHandler(m_testProgram, std::move(timeService));
	}

	service::ITestStepEndEventHandler* StubServicesFactory::buildTestStepEndEventHandlerStub() const
	{
		auto timeService = buildTimeService();
		return new service::TestStepEndEventHandler(m_testProgram, std::move(timeService));
	}

	service::ITestCaseEndEventHandler* StubServicesFactory::buildTestCaseEndEventHandlerStub() const
	{
		auto timeService = buildTimeService();
		return new service::TestCaseEndEventHandler(m_testProgram, std::move(timeService));
	}

	service::ITestSuiteEndEventHandler* StubServicesFactory::buildTestSuiteEndEventHandlerStub() const
	{
		auto timeService = buildTimeService();
		return new service::TestSuiteEndEventHandler(m_testProgram, std::move(timeService));
	}

	service::ITestProgramEndEventHandler* StubServicesFactory::buildTestProgramEndEventHandlerStub() const
	{
		auto testProgramJSONBuilder = buildTestProgramJSONBuilder();
		return new service::TestProgramEndEventHandler(m_testProgram, std::move(testProgramJSONBuilder));
	}


	// Property services
	service::ITestSuitePropertySetter* StubServicesFactory::buildTestSuitePropertySetterStub() const
	{
		return new service::TestSuitePropertySetter(m_testProgram);
	}

	service::ITestCasePropertySetter* StubServicesFactory::buildTestCasePropertySetterStub() const
	{
		return new service::TestCasePropertySetter(m_testProgram);
	}


	// Report services
	service::ITestProgramJSONBuilder* StubServicesFactory::buildTestProgramJSONBuilderStub() const
	{
		auto fileService = buildFileService();
		auto testSuiteJSONSerializer = buildTestSuiteJSONSerializer();
		return new service::TestProgramJSONBuilder(std::move(testSuiteJSONSerializer), std::move(fileService));
	}

	service::ITestSuiteJSONSerializer* StubServicesFactory::buildTestSuiteJSONSerializerStub() const
	{
		auto jsonAdapter = std::make_unique<json::rapidjson::JSONAdapter>();
		return new service::TestSuiteJSONSerializer(std::move(jsonAdapter));
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

