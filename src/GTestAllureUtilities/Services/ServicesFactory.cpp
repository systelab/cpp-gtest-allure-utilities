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


namespace systelab { namespace gtest_allure_utilities { namespace service {

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

		return std::unique_ptr<::testing::TestEventListener>(new GTestEventListener
					(std::move(testProgramStartEventHandler), std::move(testCaseStartEventHandler),
					 std::move(testCaseEndEventHandler), std::move(testProgramEndEventHandler)) );
	}

	// Lifecycle events handling services
	std::unique_ptr<ITestProgramStartEventHandler> ServicesFactory::buildTestProgramStartEventHandler() const
	{
		return std::unique_ptr<TestProgramStartEventHandler>(new TestProgramStartEventHandler(m_testSuite));
	}

	std::unique_ptr<ITestCaseStartEventHandler> ServicesFactory::buildTestCaseStartEventHandler() const
	{
		auto timeService = buildTimeService();
		auto uuidGeneratorService = buildUUIDGeneratorService();
		return std::unique_ptr<TestCaseStartEventHandler>(new TestCaseStartEventHandler(
			m_testSuite, std::move(uuidGeneratorService), std::move(timeService)) );
	}

	std::unique_ptr<ITestCaseEndEventHandler> ServicesFactory::buildTestCaseEndEventHandler() const
	{
		auto timeService = buildTimeService();
		return std::unique_ptr<TestCaseEndEventHandler>(new TestCaseEndEventHandler(
			m_testSuite, std::move(timeService)) );
	}

	std::unique_ptr<ITestProgramEndEventHandler> ServicesFactory::buildTestProgramEndEventHandler() const
	{
		auto testSuiteJSONBuilder = buildTestSuiteJSONBuilder();
		return std::unique_ptr<TestProgramEndEventHandler>(new TestProgramEndEventHandler(
			m_testSuite, std::move(testSuiteJSONBuilder)));
	}

	// JSON services
	std::unique_ptr<ITestSuiteJSONBuilder> ServicesFactory::buildTestSuiteJSONBuilder() const
	{
		auto fileService = buildFileService();
		auto testCaseJSONSerializer = buildTestCaseJSONSerializer();
		return std::unique_ptr<TestSuiteJSONBuilder>( new TestSuiteJSONBuilder(
			std::move(testCaseJSONSerializer), std::move(fileService)) );
	}

	std::unique_ptr<ITestCaseJSONSerializer> ServicesFactory::buildTestCaseJSONSerializer() const
	{
		return std::unique_ptr<TestCaseJSONSerializer>(new TestCaseJSONSerializer());
	}

	// System services
	std::unique_ptr<IUUIDGeneratorService> ServicesFactory::buildUUIDGeneratorService() const
	{
		return std::unique_ptr<UUIDGeneratorService>(new UUIDGeneratorService());
	}

	std::unique_ptr<IFileService> ServicesFactory::buildFileService() const
	{
		return std::unique_ptr<FileService>(new FileService());
	}

	std::unique_ptr<ITimeService> ServicesFactory::buildTimeService() const
	{
		return std::unique_ptr<TimeService>(new TimeService());
	}

}}}
