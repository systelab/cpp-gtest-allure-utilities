#include "TestStepStartEventHandler.h"

#include "Model/Action.h"
#include "Model/ExpectedResult.h"
#include "Model/TestProgram.h"
#include "Services/System/ITimeService.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestStepStartEventHandler::TestStepStartEventHandler(model::TestProgram& testProgram,
														 std::unique_ptr<ITimeService> timeService)
		:m_testProgram(testProgram)
		,m_timeService(std::move(timeService))
	{
	}

	void TestStepStartEventHandler::handleTestStepStart(const std::string& testStepName, bool isAction) const
	{
		auto step = buildStep(isAction);
		step->setName(testStepName);
		step->setStart(m_timeService->getCurrentTime());
		step->setStage(model::Stage::RUNNING);
		step->setStatus(model::Status::UNKNOWN);

		auto& testCase = getRunningTestCase();
		testCase.addStep(std::move(step));
	}

	std::unique_ptr<model::Step> TestStepStartEventHandler::buildStep(bool isAction) const
	{
		if (isAction)
		{
			return std::make_unique<model::Action>();
		}
		else
		{
			return std::make_unique<model::ExpectedResult>();
		}
	}

	model::TestCase& TestStepStartEventHandler::getRunningTestCase() const
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

	model::TestSuite& TestStepStartEventHandler::getRunningTestSuite() const
	{
		unsigned int nTestSuites = (unsigned int)m_testProgram.getTestSuitesCount();
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
