#include "ServicesFactory.h"

#include "Model/TestSuite.h"
#include "Services/EventHandlers/TestCaseEndEventHandler.h"
#include "Services/EventHandlers/TestCaseStartEventHandler.h"
#include "Services/EventHandlers/TestProgramEndEventHandler.h"
#include "Services/EventHandlers/TestProgramStartEventHandler.h"
#include "Services/GoogleTest/GTestEventListener.h"
#include "Services/System/FileService.h"
#include "Services/System/TimeService.h"
#include "Services/System/UUIDGeneratorService.h"
#include "Services/Report/TestCaseJSONSerializer.h"
#include "Services/Report/TestSuiteJSONBuilder.h"

#include "RapidJSONAdapter/JSONAdapter.h"


namespace systelab { namespace gtest_allure { namespace service {

	ServicesFactory::ServicesFactory(model::TestSuite& testSuite)
		:m_testSuite(testSuite)
	{
	}


	// GTest services
	std::unique_ptr<::testing::TestEventListener> ServicesFactory::buildGTestEventListener() const
	{
		auto testProgramStartEventHandler = buildTestProgramStartEventHandler();
		auto testCaseStartEventHandler = buildTestCaseStartEventHandler();
		auto testCaseEndEventHandler = buildTestCaseEndEventHandler();
		auto testProgramEndEventHandler = buildTestProgramEndEventHandler();

		return std::make_unique<GTestEventListener>(std::move(testProgramStartEventHandler), std::move(testCaseStartEventHandler),
													std::move(testCaseEndEventHandler), std::move(testProgramEndEventHandler));
	}


	// Lifecycle events handling services
	std::unique_ptr<ITestProgramStartEventHandler> ServicesFactory::buildTestProgramStartEventHandler() const
	{
		return std::make_unique<TestProgramStartEventHandler>(m_testSuite);
	}

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

	std::unique_ptr<ITestProgramEndEventHandler> ServicesFactory::buildTestProgramEndEventHandler() const
	{
		auto testSuiteJSONBuilder = buildTestSuiteJSONBuilder();
		return std::make_unique<TestProgramEndEventHandler>(m_testSuite, std::move(testSuiteJSONBuilder));
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
		auto jsonAdapter = std::make_unique<json::rapidjson::JSONAdapter>();
		return std::make_unique<TestCaseJSONSerializer>(std::move(jsonAdapter));
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
