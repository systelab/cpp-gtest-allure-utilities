#include "TestCaseEndEventHandler.h"

#include "Model/TestSuite.h"
#include "Services/System/ITimeService.h"


namespace systelab { namespace gtest_allure_utilities { namespace service {

	TestCaseEndEventHandler::TestCaseEndEventHandler(model::TestSuite& testSuite,
													 std::unique_ptr<ITimeService> timeService)
		:m_testSuite(testSuite)
		,m_timeService(std::move(timeService))
	{
	}

	void TestCaseEndEventHandler::handleTestCaseEnd(model::Status status) const
	{
		model::TestCase& testCase = getRunningTestCase();
		testCase.setStop(m_timeService->getCurrentTime());
		testCase.setStage(model::Stage::FINISHED);
		testCase.setStatus(status);
	}

	model::TestCase& TestCaseEndEventHandler::getRunningTestCase() const
	{
		unsigned nTestCase = m_testSuite.getTestCasesCount();
		for (unsigned i = 0; i < nTestCase; i++)
		{
			model::TestCase& testCase = m_testSuite.getTestCase(i);
			if (testCase.getStage() == model::Stage::RUNNING)
			{
				return testCase;
			}
		}

		throw std::exception("TestCaseEndEventHandler::getRunningTestCase() No running test case");
	}

}}}
