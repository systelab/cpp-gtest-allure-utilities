#include "stdafx.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestCaseEndEventHandler.h"

#include "GTestAllureUtilities/Model/TestProgram.h"

#include "TestUtilities/Mocks/Services/System/MockTimeService.h"
#include "TestUtilities/Mocks/Services/System/MockUUIDGeneratorService.h"


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class TestCaseEndEventHandlerTest : public testing::Test
	{
	public:
		void SetUp()
		{
			setUpTestProgram();
			auto timeService = buildTimeService();

			m_service = std::make_unique<service::TestCaseEndEventHandler>(m_testProgram, std::move(timeService));
		}

		void setUpTestProgram()
		{
			model::TestSuite finishedTestSuite;
			finishedTestSuite.addTestCase(buildTestCase("TC-1.1", model::Stage::FINISHED));
			finishedTestSuite.addTestCase(buildTestCase("TC-1.2", model::Stage::FINISHED));
			m_testProgram.addTestSuite(finishedTestSuite);

			model::TestSuite runningTestSuite;
			runningTestSuite.addTestCase(buildTestCase("TC-2.1", model::Stage::FINISHED));
			runningTestSuite.addTestCase(buildTestCase("TC-2.2", model::Stage::RUNNING));
			m_testProgram.addTestSuite(runningTestSuite);

			m_runningTestCase = &m_testProgram.getTestSuite(1).getTestCases()[1];
		}

		model::TestCase buildTestCase(const std::string& name, model::Stage stage)
		{
			model::Action testCaseAction;
			testCaseAction.setName("Test case action");
			testCaseAction.setStage(stage);

			model::TestCase testCase;
			testCase.setName(name);
			testCase.addAction(testCaseAction);

			return testCase;
		}

		std::unique_ptr<service::ITimeService> buildTimeService()
		{
			auto timeService = std::unique_ptr<MockTimeService>(new MockTimeService());
			m_timeService = timeService.get();

			m_currentTime = 123456789;
			ON_CALL(*m_timeService, getCurrentTime()).WillByDefault(Return(m_currentTime));

			return timeService;
		}

	protected:
		std::unique_ptr<service::TestCaseEndEventHandler> m_service;
		model::TestProgram m_testProgram;
		MockTimeService* m_timeService;

		model::TestCase* m_runningTestCase;
		time_t m_currentTime;
	};


	TEST_F(TestCaseEndEventHandlerTest, testHandleTestCaseEndSetsStopTimeOfRunningTestCaseToCurrentTime)
	{
		m_service->handleTestCaseEnd(model::Status::PASSED);
		ASSERT_EQ(m_currentTime, m_runningTestCase->getActions()[0].getStop());
	}

	TEST_F(TestCaseEndEventHandlerTest, testHandleTestCaseEndSetsStageOfRunningTestCaseToFinished)
	{
		m_service->handleTestCaseEnd(model::Status::PASSED);
		ASSERT_EQ(model::Stage::FINISHED, m_runningTestCase->getActions()[0].getStage());
	}

	TEST_F(TestCaseEndEventHandlerTest, testHandleTestCaseEndThrowsExceptionWhenNoRunningTestCase)
	{
		m_runningTestCase->getActions()[0].setStage(model::Stage::FINISHED);
		ASSERT_THROW(m_service->handleTestCaseEnd(model::Status::PASSED), service::ITestCaseEndEventHandler::NoRunningTestCaseException);
	}


	class TestCaseEndEventHandlerStatusTest : public TestCaseEndEventHandlerTest
											, public testing::WithParamInterface<model::Status>
	{
	public:
		void SetUp()
		{
			TestCaseEndEventHandlerTest::SetUp();
		}
	};

	TEST_P(TestCaseEndEventHandlerStatusTest, testHandleTestCaseEndSetsStatusOfRunningTestCaseToGivenValue)
	{
		m_service->handleTestCaseEnd(GetParam());
		ASSERT_EQ(GetParam(), m_runningTestCase->getActions()[0].getStatus());
	}

	std::vector<model::Status> testStatusData = { model::Status::BROKEN, model::Status::FAILED, model::Status::PASSED,
												  model::Status::SKIPPED, model::Status::UNKNOWN };

	INSTANTIATE_TEST_CASE_P(Test, TestCaseEndEventHandlerStatusTest, ValuesIn(testStatusData));

}}}
