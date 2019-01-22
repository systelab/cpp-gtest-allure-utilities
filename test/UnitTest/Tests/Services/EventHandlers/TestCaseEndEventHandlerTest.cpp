#include "GTestAllureUtilities/Services/EventHandlers/TestCaseEndEventHandler.h"

#include "GTestAllureUtilities/Model/TestSuite.h"

#include "TestUtilities/Mocks/Services/System/MockTimeService.h"
#include "TestUtilities/Mocks/Services/System/MockUUIDGeneratorService.h"

#include <gtest/gtest.h>


using namespace testing;
using namespace systelab::gtest_allure_utilities;
using namespace systelab::gtest_allure_utilities::test_utility;

namespace systelab { namespace gtest_allure_utilities { namespace unit_test {

	class TestCaseEndEventHandlerTest : public testing::Test
	{
	public:
		void SetUp()
		{
			setUpTestSuite();
			auto timeService = buildTimeService();

			m_service = std::unique_ptr<service::TestCaseEndEventHandler>(new service::TestCaseEndEventHandler
							(m_testSuite, std::move(timeService)) );
		}

		void setUpTestSuite()
		{
			model::TestCase finishedTestCase;
			finishedTestCase.setName("Finished test case");
			finishedTestCase.setStage(model::Stage::FINISHED);
			m_testSuite.addTestCase(finishedTestCase);

			model::TestCase runningTestCase;
			runningTestCase.setName("Running test case");
			runningTestCase.setStage(model::Stage::RUNNING);
			m_testSuite.addTestCase(runningTestCase);

			m_runningTestCase = &m_testSuite.getTestCase(1);
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
		model::TestSuite m_testSuite;
		MockTimeService* m_timeService;

		model::TestCase* m_runningTestCase;
		time_t m_currentTime;
	};


	TEST_F(TestCaseEndEventHandlerTest, testHandleTestCaseEndSetsStopTimeOfRunningTestCaseToCurrentTime)
	{
		m_service->handleTestCaseEnd(model::Status::PASSED);
		ASSERT_EQ(m_currentTime, m_runningTestCase->getStop());
	}

	TEST_F(TestCaseEndEventHandlerTest, testHandleTestCaseEndSetsStageOfRunningTestCaseToFinished)
	{
		m_service->handleTestCaseEnd(model::Status::PASSED);
		ASSERT_EQ(model::Stage::FINISHED, m_runningTestCase->getStage());
	}

	TEST_F(TestCaseEndEventHandlerTest, testHandleTestCaseEndThrowsExceptionWhenNoRunningTestCase)
	{
		m_runningTestCase->setStage(model::Stage::FINISHED);
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
		ASSERT_EQ(GetParam(), m_runningTestCase->getStatus());
	}

	std::vector<model::Status> testStatusData = { model::Status::BROKEN, model::Status::FAILED, model::Status::PASSED,
												  model::Status::SKIPPED, model::Status::UNKNOWN };

	INSTANTIATE_TEST_CASE_P(Test, TestCaseEndEventHandlerStatusTest, ValuesIn(testStatusData));

}}}
