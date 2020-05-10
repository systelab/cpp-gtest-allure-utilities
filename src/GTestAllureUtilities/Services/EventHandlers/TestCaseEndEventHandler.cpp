#include "TestCaseEndEventHandler.h"

#include "Model/TestProgram.h"
#include "Services/System/ITimeService.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestCaseEndEventHandler::TestCaseEndEventHandler(model::TestProgram& testProgram,
													 std::unique_ptr<ITimeService> timeService)
		:m_testProgram(testProgram)
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
		auto& testSuite = getRunningTestSuite();
		for (model::TestCase& testCase : testSuite.getTestCases())
		{
			if (testCase.getStage() == model::Stage::RUNNING)
			{
				return testCase;
			}
		}

		throw NoRunningTestCaseException();
	}

	model::TestSuite& TestCaseEndEventHandler::getRunningTestSuite() const
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
