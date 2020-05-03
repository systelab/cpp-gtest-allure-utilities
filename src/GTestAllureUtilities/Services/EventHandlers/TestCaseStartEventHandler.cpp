#include "TestCaseStartEventHandler.h"

#include "Model/TestSuite.h"
#include "Services/Report/ITestCaseJSONSerializer.h"
#include "Services/System/IFileService.h"
#include "Services/System/ITimeService.h"
#include "Services/System/IUUIDGeneratorService.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestCaseStartEventHandler::TestCaseStartEventHandler(model::TestSuite& testSuite,
														 std::unique_ptr<IUUIDGeneratorService> uuidGeneratorService,
														 std::unique_ptr<ITimeService> timeService)
		:m_testSuite(testSuite)
		,m_uuidGeneratorService(std::move(uuidGeneratorService))
		,m_timeService(std::move(timeService))
	{
	}

	void TestCaseStartEventHandler::handleTestCaseStart(const std::string& testCaseName) const
	{
		model::TestCase testCase;
		testCase.setName(testCaseName);
		testCase.setUUID(m_uuidGeneratorService->generateUUID());
		testCase.setStart(m_timeService->getCurrentTime());
		testCase.setStage(model::Stage::RUNNING);
		testCase.setStatus(model::Status::UNKNOWN);
		m_testSuite.addTestCase(testCase);
	}

}}}
