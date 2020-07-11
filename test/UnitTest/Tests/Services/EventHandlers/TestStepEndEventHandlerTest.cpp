#include "stdafx.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestStepEndEventHandler.h"

#include "GTestAllureUtilities/Model/TestProgram.h"
#include "GTestAllureUtilities/Model/Action.h"

#include "TestUtilities/Mocks/Services/System/MockTimeService.h"
#include "TestUtilities/Mocks/Services/System/MockUUIDGeneratorService.h"


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class TestStepEndEventHandlerTest : public testing::Test
	{
	public:
		void SetUp()
		{
			auto timeService = buildTimeService();
			setUpTestProgram();

			m_service = std::make_unique<service::TestStepEndEventHandler>(m_testProgram, std::move(timeService));
		}

		std::unique_ptr<service::ITimeService> buildTimeService()
		{
			auto timeService = std::make_unique<MockTimeService>();
			m_timeService = timeService.get();

			m_currentTime = 123456789;
			ON_CALL(*m_timeService, getCurrentTime()).WillByDefault(Return(m_currentTime));

			return timeService;
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

			m_runningTestStep = m_testProgram.getTestSuite(1).getTestCases()[1].getStep(1);
		}

		model::TestCase buildTestCase(const std::string& name, model::Stage stage)
		{
			model::TestCase testCase;
			testCase.setName(name);
			testCase.setStage(stage);
			testCase.setStatus(model::Status::UNKNOWN);

			testCase.addStep(buildTestCaseStep(name + "-Action1", model::Stage::FINISHED));

			if (stage == model::Stage::RUNNING)
			{
				testCase.addStep(buildTestCaseStep(name + "-Action2", model::Stage::RUNNING));
			}

			return testCase;
		}

		std::unique_ptr<model::Step> buildTestCaseStep(const std::string& name, model::Stage stage)
		{
			auto step = std::make_unique<model::Action>();
			step->setName(name);
			step->setStart(m_timeService->getCurrentTime());
			step->setStage(stage);
			step->setStatus(model::Status::UNKNOWN);

			return step;
		}

	protected:
		std::unique_ptr<service::TestStepEndEventHandler> m_service;
		model::TestProgram m_testProgram;
		MockTimeService* m_timeService;

		model::Step* m_runningTestStep;
		time_t m_currentTime;
	};


	TEST_F(TestStepEndEventHandlerTest, testHandleTestStepEndSetsStopTimeOfRunningTestStepToCurrentTime)
	{
		m_service->handleTestStepEnd(model::Status::PASSED);
		ASSERT_EQ(m_currentTime, m_runningTestStep->getStop());
	}

	TEST_F(TestStepEndEventHandlerTest, testHandleTestStepEndSetsStageOfRunningTestStepToFinished)
	{
		m_service->handleTestStepEnd(model::Status::PASSED);
		ASSERT_EQ(model::Stage::FINISHED, m_runningTestStep->getStage());
	}

	TEST_F(TestStepEndEventHandlerTest, testHandleTestStepEndThrowsExceptionWhenNoRunningTestStep)
	{
		m_runningTestStep->setStage(model::Stage::FINISHED);
		ASSERT_THROW(m_service->handleTestStepEnd(model::Status::PASSED),
					 service::ITestStepEndEventHandler::NoRunningTestStepException);
	}

	TEST_F(TestStepEndEventHandlerTest, testHandleTestStepEndThrowsExceptionWhenNoRunningTestCase)
	{
		m_testProgram.getTestSuite(1).getTestCases()[1].setStage(model::Stage::FINISHED);
		ASSERT_THROW(m_service->handleTestStepEnd(model::Status::PASSED),
					 service::ITestStepEndEventHandler::NoRunningTestCaseException);
	}

	TEST_F(TestStepEndEventHandlerTest, testHandleTestStepEndThrowsExceptionWhenNoRunningTestSuite)
	{
		m_testProgram.getTestSuite(1).setStage(model::Stage::FINISHED);
		ASSERT_THROW(m_service->handleTestStepEnd(model::Status::PASSED),
					 service::ITestStepEndEventHandler::NoRunningTestSuiteException);
	}


	class TestStepEndEventHandlerStatusTest : public TestStepEndEventHandlerTest
											, public testing::WithParamInterface<model::Status>
	{
	public:
		void SetUp()
		{
			TestStepEndEventHandlerTest::SetUp();
		}
	};

	TEST_P(TestStepEndEventHandlerStatusTest, testHandleTestStepEndSetsStatusOfRunningTestStepToGivenValue)
	{
		m_service->handleTestStepEnd(GetParam());
		ASSERT_EQ(GetParam(), m_runningTestStep->getStatus());
	}

	namespace {
		std::vector<model::Status> testStatusData = { model::Status::BROKEN, model::Status::FAILED, model::Status::PASSED,
													  model::Status::SKIPPED, model::Status::UNKNOWN };
	}

	INSTANTIATE_TEST_SUITE_P(Test, TestStepEndEventHandlerStatusTest, ValuesIn(testStatusData));

}}}
