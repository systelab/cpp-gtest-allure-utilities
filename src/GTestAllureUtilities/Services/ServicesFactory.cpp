#include "ServicesFactory.h"

#include "Model/TestSuite.h"
#include "Services/EventHandlers/TestCaseStartEventHandler.h"
#include "Services/EventHandlers/TestCaseEndEventHandler.h"
#include "Services/GoogleTest/GTestEventListener.h"
#include "Services/System/FileService.h"
#include "Services/System/TimeService.h"
#include "Services/System/UUIDGeneratorService.h"
#include "Services/Report/TestCaseJSONSerializer.h"
#include "Services/Report/TestSuiteJSONBuilder.h"


namespace systelab { namespace gtest_allure_utilities { namespace service {

	ServicesFactory::ServicesFactory(model::TestSuite& testSuite)
		:m_testSuite(testSuite)
	{
	}

	// GTest services
	std::unique_ptr<::testing::TestEventListener> ServicesFactory::buildGTestEventListener() const
	{
		auto testCaseStartEventHandler = buildTestCaseStartEventHandler();
		auto testCaseEndEventHandler = buildTestCaseEndEventHandler();
		auto testSuiteJSONBuilder = buildTestSuiteJSONBuilder();
		return std::make_unique<GTestEventListener>(m_testSuite, std::move(testCaseStartEventHandler),
													std::move(testCaseEndEventHandler), std::move(testSuiteJSONBuilder));
	}

	// Lifecycle events handling services
	std::unique_ptr<ITestCaseStartEventHandler> ServicesFactory::buildTestCaseStartEventHandler() const
	{
		auto timeService = buildTimeService();
		auto uuidGeneratorService = buildUUIDGeneratorService();
		return std::make_unique<TestCaseStartEventHandler>(m_testSuite, std::move(uuidGeneratorService), std::move(timeService));
	}

	std::unique_ptr<ITestCaseEndEventHandler> ServicesFactory::buildTestCaseEndEventHandler() const
	{
		auto timeService = buildTimeService();
		return std::make_unique<TestCaseEndEventHandler>(m_testSuite, std::move(timeService));
	}

	// JSON services
	std::unique_ptr<ITestSuiteJSONBuilder> ServicesFactory::buildTestSuiteJSONBuilder() const
	{
		auto fileService = buildFileService();
		auto testCaseJSONSerializer = buildTestCaseJSONSerializer();
		return std::make_unique<TestSuiteJSONBuilder>(std::move(testCaseJSONSerializer), std::move(fileService));
	}

	std::unique_ptr<ITestCaseJSONSerializer> ServicesFactory::buildTestCaseJSONSerializer() const
	{
		return std::make_unique<TestCaseJSONSerializer>();
	}

	// System services
	std::unique_ptr<IUUIDGeneratorService> ServicesFactory::buildUUIDGeneratorService() const
	{
		return std::make_unique<UUIDGeneratorService>();
	}

	std::unique_ptr<IFileService> ServicesFactory::buildFileService() const
	{
		return std::make_unique<FileService>();
	}

	std::unique_ptr<ITimeService> ServicesFactory::buildTimeService() const
	{
		return std::make_unique<TimeService>();
	}

}}}
