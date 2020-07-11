#include "stdafx.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestStepStartEventHandler.h"

#include "GTestAllureUtilities/Model/StepType.h"
#include "GTestAllureUtilities/Model/TestProgram.h"

#include "TestUtilities/Mocks/Services/System/MockTimeService.h"


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class TestStepStartEventHandlerTest : public testing::Test
	{
		void SetUp()
		{
			setUpTestProgram();
			auto timeService = buildTimeService();

			m_service = std::make_unique<service::TestStepStartEventHandler>(m_testProgram, std::move(timeService));
		}

		void setUpTestProgram()
		{
			model::TestSuite finishedTestSuite;
			finishedTestSuite.setStage(model::Stage::FINISHED);
			finishedTestSuite.addTestCase(buildTestCase("TC-1.1", model::Stage::FINISHED));
			finishedTestSuite.addTestCase(buildTestCase("TC-1.2", model::Stage::FINISHED));
			m_testProgram.addTestSuite(finishedTestSuite);

			model::TestSuite runningTestSuite;
			runningTestSuite.setStage(model::Stage::RUNNING);
			runningTestSuite.addTestCase(buildTestCase("TC-2.1", model::Stage::FINISHED));
			runningTestSuite.addTestCase(buildTestCase("TC-2.2", model::Stage::RUNNING));
			m_testProgram.addTestSuite(runningTestSuite);

			m_runningTestCase = &(m_testProgram.getTestSuite(1).getTestCases()[1]);
		}

		model::TestCase buildTestCase(const std::string& name, model::Stage stage)
		{
			model::TestCase testCase;
			testCase.setName(name);
			testCase.setStage(stage);
			testCase.setStatus(model::Status::UNKNOWN);

			return testCase;
		}

		std::unique_ptr<service::ITimeService> buildTimeService()
		{
			auto timeService = std::make_unique<MockTimeService>();
			m_timeService = timeService.get();

			m_currentTime = 987654321;
			ON_CALL(*m_timeService, getCurrentTime()).WillByDefault(Return(m_currentTime));

			return timeService;
		}

	protected:
		std::unique_ptr<service::TestStepStartEventHandler> m_service;
		model::TestProgram m_testProgram;
		MockTimeService* m_timeService;

		model::TestCase* m_runningTestCase;
		time_t m_currentTime;
	};


	TEST_F(TestStepStartEventHandlerTest, testHandleTestStepStartAddsStartedActionStepIntoRunningTestCase)
	{
		std::string startedActionName = "StartedAction";
		bool isActionStep = true;
		m_service->handleTestStepStart(startedActionName, isActionStep);

		ASSERT_EQ(1, m_runningTestCase->getStepCount());

		const model::Step& addedTestStep = *m_runningTestCase->getStep(0);
		EXPECT_EQ(startedActionName, addedTestStep.getName());
		EXPECT_EQ(model::StepType::ACTION_STEP, addedTestStep.getStepType());
		EXPECT_EQ(m_currentTime, addedTestStep.getStart());
		EXPECT_EQ(model::Stage::RUNNING, addedTestStep.getStage());
		EXPECT_EQ(model::Status::UNKNOWN, addedTestStep.getStatus());
	}

	TEST_F(TestStepStartEventHandlerTest, testHandleTestStepStartAddsStartedExpectedResultStepIntoRunningTestCase)
	{
		std::string startedExpectedResultName = "StartedExpectedResult";
		bool isActionStep = false;
		m_service->handleTestStepStart(startedExpectedResultName, isActionStep);

		ASSERT_EQ(1, m_runningTestCase->getStepCount());

		const model::Step& addedTestStep = *m_runningTestCase->getStep(0);
		EXPECT_EQ(startedExpectedResultName, addedTestStep.getName());
		EXPECT_EQ(model::StepType::EXPECTED_RESULT_STEP, addedTestStep.getStepType());
		EXPECT_EQ(m_currentTime, addedTestStep.getStart());
		EXPECT_EQ(model::Stage::RUNNING, addedTestStep.getStage());
		EXPECT_EQ(model::Status::UNKNOWN, addedTestStep.getStatus());
	}

	TEST_F(TestStepStartEventHandlerTest, testHandleTestStepStartThrowsExceptionWhenNoRunningTestSuite)
	{
		m_testProgram.clearTestSuites();
		ASSERT_THROW(m_service->handleTestStepStart("StartedStep", true),
					 service::TestStepStartEventHandler::NoRunningTestSuiteException);
	}

	TEST_F(TestStepStartEventHandlerTest, testHandleTestStepStartThrowsExceptionWhenNoRunningTestCase)
	{
		m_testProgram.getTestSuite(1).clearTestCases();
		ASSERT_THROW(m_service->handleTestStepStart("StartedStep", true),
			service::TestStepStartEventHandler::NoRunningTestCaseException);
	}

}}}
