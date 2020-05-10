#include "TestCaseStartEventHandler.h"

#include "Model/TestProgram.h"
#include "Services/System/ITimeService.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestCaseStartEventHandler::TestCaseStartEventHandler(model::TestProgram& testProgram,
														 std::unique_ptr<ITimeService> timeService)
		:m_testProgram(testProgram)
		,m_timeService(std::move(timeService))
	{
	}

	void TestCaseStartEventHandler::handleTestCaseStart(const std::string& testCaseName) const
	{
		model::TestCase testCase;
		testCase.setName(testCaseName);
		testCase.setStart(m_timeService->getCurrentTime());
		testCase.setStage(model::Stage::RUNNING);
		testCase.setStatus(model::Status::UNKNOWN);

		auto& testSuite = getRunningTestSuite();
		testSuite.addTestCase(testCase);
	}

	model::TestSuite& TestCaseStartEventHandler::getRunningTestSuite() const
	{
		unsigned int nTestSuites = (unsigned int) m_testProgram.getTestSuitesCount();
		for (unsigned int i = 0; i < nTestSuites; i++)
		{
			model::TestSuite& testSuite = m_testProgram.getTestSuite(i);
			if (testSuite.getStage() == model::Stage::RUNNING)
			{
				return testSuite;
			}
		}

		throw NoRunningTestSuiteException();
	}

}}}
