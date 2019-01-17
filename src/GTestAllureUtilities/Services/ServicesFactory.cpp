#include "ServicesFactory.h"

#include "Model/TestSuite.h"
#include "Services/FileService.h"
#include "Services/GTestEventListener.h"
#include "Services/TestCaseJSONSerializer.h"
#include "Services/TestCaseStartEventHandler.h"
#include "Services/TestSuiteJSONBuilder.h"
#include "Services/UUIDGeneratorService.h"


namespace systelab { namespace gtest_allure_utilities { namespace service {

	ServicesFactory::ServicesFactory(model::TestSuite& testSuite)
		:m_testSuite(testSuite)
	{
	}

	// GTest services
	std::unique_ptr<::testing::TestEventListener> ServicesFactory::buildGTestEventListener() const
	{
		auto testCaseStartEventHandler = buildTestCaseStartEventHandler();
		auto testSuiteJSONBuilder = buildTestSuiteJSONBuilder();
		return std::make_unique<GTestEventListener>(m_testSuite, std::move(testCaseStartEventHandler), std::move(testSuiteJSONBuilder));
	}

	// Lifecycle events handling services
	std::unique_ptr<ITestCaseStartEventHandler> ServicesFactory::buildTestCaseStartEventHandler() const
	{
		throw;
	}

	std::unique_ptr<ITestCaseEndEventHandler> ServicesFactory::buildTestCaseEndEventHandler() const
	{
		throw;
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

}}}
