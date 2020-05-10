#include "TestSuiteStartEventHandler.h"

#include "Model/TestProgram.h"
#include "Services/Report/ITestSuiteJSONSerializer.h"
#include "Services/System/IFileService.h"
#include "Services/System/ITimeService.h"
#include "Services/System/IUUIDGeneratorService.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestSuiteStartEventHandler::TestSuiteStartEventHandler(model::TestProgram& testProgram,
														   std::unique_ptr<IUUIDGeneratorService> uuidGeneratorService,
														   std::unique_ptr<ITimeService> timeService)
		:m_testProgram(testProgram)
		,m_uuidGeneratorService(std::move(uuidGeneratorService))
		,m_timeService(std::move(timeService))
	{
	}

	void TestSuiteStartEventHandler::handleTestSuiteStart(const std::string& testSuiteName) const
	{
		model::TestSuite testSuite;
		testSuite.setUUID(m_uuidGeneratorService->generateUUID());
		testSuite.setName(testSuiteName);
		testSuite.setStart(m_timeService->getCurrentTime());
		testSuite.setStage(model::Stage::RUNNING);
		testSuite.setStatus(model::Status::UNKNOWN);
		m_testProgram.addTestSuite(testSuite);
	}

}}}
