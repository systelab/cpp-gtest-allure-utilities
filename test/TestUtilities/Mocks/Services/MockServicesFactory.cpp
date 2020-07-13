#include "stdafx.h"
#include "MockServicesFactory.h"

#include "GTestAllureUtilities/Services/EventHandlers/ITestCaseEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestCaseStartEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestProgramEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestProgramStartEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestStepEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestStepStartEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestSuiteEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestSuiteStartEventHandler.h"
#include "GTestAllureUtilities/Services/GoogleTest/IGTestStatusChecker.h"
#include "GTestAllureUtilities/Services/Property/ITestSuitePropertySetter.h"
#include "GTestAllureUtilities/Services/Report/ITestSuiteJSONSerializer.h"
#include "GTestAllureUtilities/Services/Report/ITestProgramJSONBuilder.h"
#include "GTestAllureUtilities/Services/System/IFileService.h"
#include "GTestAllureUtilities/Services/System/ITimeService.h"
#include "GTestAllureUtilities/Services/System/IUUIDGeneratorService.h"


namespace systelab { namespace gtest_allure { namespace test_utility {

	MockServicesFactory::MockServicesFactory() = default;
	MockServicesFactory::~MockServicesFactory() = default;


	// GTest services
	std::unique_ptr<::testing::TestEventListener> MockServicesFactory::buildGTestEventListener() const
	{
		return std::unique_ptr<::testing::TestEventListener>(buildGTestEventListenerProxy());
	}

	std::unique_ptr<service::IGTestStatusChecker> MockServicesFactory::buildGTestStatusChecker() const
	{
		return std::unique_ptr<service::IGTestStatusChecker>(buildGTestStatusCheckerProxy());
	}


	// Lifecycle events handling services
	std::unique_ptr<service::ITestProgramStartEventHandler> MockServicesFactory::buildTestProgramStartEventHandler() const
	{
		return std::unique_ptr<service::ITestProgramStartEventHandler>(buildTestProgramStartEventHandlerProxy());
	}

	std::unique_ptr<service::ITestSuiteStartEventHandler> MockServicesFactory::buildTestSuiteStartEventHandler() const
	{
		return std::unique_ptr<service::ITestSuiteStartEventHandler>(buildTestSuiteStartEventHandlerProxy());
	}

	std::unique_ptr<service::ITestCaseStartEventHandler> MockServicesFactory::buildTestCaseStartEventHandler() const
	{
		return std::unique_ptr<service::ITestCaseStartEventHandler>(buildTestCaseStartEventHandlerProxy());
	}

	std::unique_ptr<service::ITestStepStartEventHandler> MockServicesFactory::buildTestStepStartEventHandler() const
	{
		return std::unique_ptr<service::ITestStepStartEventHandler>(buildTestStepStartEventHandlerProxy());
	}

	std::unique_ptr<service::ITestStepEndEventHandler> MockServicesFactory::buildTestStepEndEventHandler() const
	{
		return std::unique_ptr<service::ITestStepEndEventHandler>(buildTestStepEndEventHandlerProxy());
	}

	std::unique_ptr<service::ITestCaseEndEventHandler> MockServicesFactory::buildTestCaseEndEventHandler() const
	{
		return std::unique_ptr<service::ITestCaseEndEventHandler>(buildTestCaseEndEventHandlerProxy());
	}

	std::unique_ptr<service::ITestSuiteEndEventHandler> MockServicesFactory::buildTestSuiteEndEventHandler() const
	{
		return std::unique_ptr<service::ITestSuiteEndEventHandler>(buildTestSuiteEndEventHandlerProxy());
	}

	std::unique_ptr<service::ITestProgramEndEventHandler> MockServicesFactory::buildTestProgramEndEventHandler() const
	{
		return std::unique_ptr<service::ITestProgramEndEventHandler>(buildTestProgramEndEventHandlerProxy());
	}


	// Property services
	std::unique_ptr<service::ITestSuitePropertySetter> MockServicesFactory::buildTestSuitePropertySetter() const
	{
		return std::unique_ptr<service::ITestSuitePropertySetter>(buildTestSuitePropertySetterProxy());
	}


	// JSON services
	std::unique_ptr<service::ITestProgramJSONBuilder> MockServicesFactory::buildTestProgramJSONBuilder() const
	{
		return std::unique_ptr<service::ITestProgramJSONBuilder>(buildTestProgramJSONBuilderProxy());
	}

	std::unique_ptr<service::ITestSuiteJSONSerializer> MockServicesFactory::buildTestSuiteJSONSerializer() const
	{
		return std::unique_ptr<service::ITestSuiteJSONSerializer>(buildTestSuiteJSONSerializerProxy());
	}


	// System services
	std::unique_ptr<service::IUUIDGeneratorService> MockServicesFactory::buildUUIDGeneratorService() const
	{
		return std::unique_ptr<service::IUUIDGeneratorService>(buildUUIDGeneratorServiceProxy());
	}

	std::unique_ptr<service::IFileService> MockServicesFactory::buildFileService() const
	{
		return std::unique_ptr<service::IFileService>(buildFileServiceProxy());
	}

	std::unique_ptr<service::ITimeService> MockServicesFactory::buildTimeService() const
	{
		return std::unique_ptr<service::ITimeService>(buildTimeServiceProxy());
	}

}}}

