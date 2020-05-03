#include "MockServicesFactory.h"

#include "GTestAllureUtilities/Services/EventHandlers/ITestCaseEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestCaseStartEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestProgramEndEventHandler.h"
#include "GTestAllureUtilities/Services/EventHandlers/ITestProgramStartEventHandler.h"
#include "GTestAllureUtilities/Services/Report/ITestCaseJSONSerializer.h"
#include "GTestAllureUtilities/Services/Report/ITestSuiteJSONBuilder.h"
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


	// Lifecycle events handling services
	std::unique_ptr<service::ITestProgramStartEventHandler> MockServicesFactory::buildTestProgramStartEventHandler() const
	{
		return std::unique_ptr<service::ITestProgramStartEventHandler>(buildTestProgramStartEventHandlerProxy());
	}

	std::unique_ptr<service::ITestCaseStartEventHandler> MockServicesFactory::buildTestCaseStartEventHandler() const
	{
		return std::unique_ptr<service::ITestCaseStartEventHandler>(buildTestCaseStartEventHandlerProxy());
	}

	std::unique_ptr<service::ITestCaseEndEventHandler> MockServicesFactory::buildTestCaseEndEventHandler() const
	{
		return std::unique_ptr<service::ITestCaseEndEventHandler>(buildTestCaseEndEventHandlerProxy());
	}

	std::unique_ptr<service::ITestProgramEndEventHandler> MockServicesFactory::buildTestProgramEndEventHandler() const
	{
		return std::unique_ptr<service::ITestProgramEndEventHandler>(buildTestProgramEndEventHandlerProxy());
	}


	// JSON services
	std::unique_ptr<service::ITestSuiteJSONBuilder> MockServicesFactory::buildTestSuiteJSONBuilder() const
	{
		return std::unique_ptr<service::ITestSuiteJSONBuilder>(buildTestSuiteJSONBuilderProxy());
	}

	std::unique_ptr<service::ITestCaseJSONSerializer> MockServicesFactory::buildTestCaseJSONSerializer() const
	{
		return std::unique_ptr<service::ITestCaseJSONSerializer>(buildTestCaseJSONSerializerProxy());
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

