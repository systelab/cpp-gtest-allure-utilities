#include "TestSuiteEndEventHandler.h"

#include "Model/TestProgram.h"
#include "Services/System/ITimeService.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestSuiteEndEventHandler::TestSuiteEndEventHandler(model::TestProgram& testProgram,
													   std::unique_ptr<ITimeService> timeService)
		:m_testProgram(testProgram)
		,m_timeService(std::move(timeService))
	{
	}

	void TestSuiteEndEventHandler::handleTestSuiteEnd(model::Status status) const
	{
		model::TestSuite& testSuite = getRunningTestSuite();
		testSuite.setStop(m_timeService->getCurrentTime());
		testSuite.setStage(model::Stage::FINISHED);
		testSuite.setStatus(status);
	}

	model::TestSuite& TestSuiteEndEventHandler::getRunningTestSuite() const
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
