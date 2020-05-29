#include "stdafx.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestSuiteEndEventHandler.h"

#include "GTestAllureUtilities/Model/TestProgram.h"

#include "TestUtilities/Mocks/Services/System/MockTimeService.h"
#include "TestUtilities/Mocks/Services/System/MockUUIDGeneratorService.h"


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class TestSuiteEndEventHandlerTest : public testing::Test
	{
	public:
		void SetUp()
		{
			setUpTestProgram();
			auto timeService = buildTimeService();

			m_service = std::make_unique<service::TestSuiteEndEventHandler>(m_testProgram, std::move(timeService));
		}

		void setUpTestProgram()
		{
			model::TestSuite finishedTestSuite;
			finishedTestSuite.setStage(model::Stage::FINISHED);
			m_testProgram.addTestSuite(finishedTestSuite);

			model::TestSuite runningTestSuite;
			runningTestSuite.setStage(model::Stage::RUNNING);
			m_testProgram.addTestSuite(runningTestSuite);

			m_runningTestSuite = &m_testProgram.getTestSuite(1);
		}

		std::unique_ptr<service::ITimeService> buildTimeService()
		{
			auto timeService = std::make_unique<MockTimeService>();
			m_timeService = timeService.get();

			m_currentTime = 123456789;
			ON_CALL(*m_timeService, getCurrentTime()).WillByDefault(Return(m_currentTime));

			return timeService;
		}

	protected:
		std::unique_ptr<service::TestSuiteEndEventHandler> m_service;
		model::TestProgram m_testProgram;
		MockTimeService* m_timeService;

		model::TestSuite* m_runningTestSuite;
		time_t m_currentTime;
	};


	TEST_F(TestSuiteEndEventHandlerTest, testHandleTestSuiteEndSetsStopTimeOfRunningTestSuiteToCurrentTime)
	{
		m_service->handleTestSuiteEnd(model::Status::PASSED);
		ASSERT_EQ(m_currentTime, m_runningTestSuite->getStop());
	}

	TEST_F(TestSuiteEndEventHandlerTest, testHandleTestSuiteEndSetsStageOfRunningTestSuiteToFinished)
	{
		m_service->handleTestSuiteEnd(model::Status::PASSED);
		ASSERT_EQ(model::Stage::FINISHED, m_runningTestSuite->getStage());
	}

	TEST_F(TestSuiteEndEventHandlerTest, testHandleTestSuiteEndAddsTMSLinkWithSuiteTmsIdAndDefaultPattern)
	{
		m_runningTestSuite->setTmsId("MyID-123");

		m_service->handleTestSuiteEnd(model::Status::PASSED);

		auto testSuiteLinks = m_runningTestSuite->getLinks();
		ASSERT_EQ(1, testSuiteLinks.size());
		ASSERT_EQ("tms", testSuiteLinks[0].getType());
		ASSERT_EQ("MyID-123", testSuiteLinks[0].getName());
		ASSERT_EQ("http://MyID-123", testSuiteLinks[0].getURL());
	}

	TEST_F(TestSuiteEndEventHandlerTest, testHandleTestSuiteEndAddsTMSLinkWithSuiteTmsIdAndCustomPattern)
	{
		m_testProgram.setTMSLinksPattern("https://www.mycompany.com/{}/page");
		m_runningTestSuite->setTmsId("9876");

		m_service->handleTestSuiteEnd(model::Status::PASSED);

		auto testSuiteLinks = m_runningTestSuite->getLinks();
		ASSERT_EQ(1, testSuiteLinks.size());
		ASSERT_EQ("tms", testSuiteLinks[0].getType());
		ASSERT_EQ("9876", testSuiteLinks[0].getName());
		ASSERT_EQ("https://www.mycompany.com/9876/page", testSuiteLinks[0].getURL());
	}

	TEST_F(TestSuiteEndEventHandlerTest, testHandleTestSuiteEndThrowsExceptionWhenNoRunningTestSuite)
	{
		m_runningTestSuite->setStage(model::Stage::FINISHED);
		ASSERT_THROW(m_service->handleTestSuiteEnd(model::Status::PASSED), service::ITestSuiteEndEventHandler::NoRunningTestSuiteException);
	}


	class TestSuiteEndEventHandlerStatusTest : public TestSuiteEndEventHandlerTest
											 , public testing::WithParamInterface<model::Status>
	{
	public:
		void SetUp()
		{
			TestSuiteEndEventHandlerTest::SetUp();
		}
	};

	TEST_P(TestSuiteEndEventHandlerStatusTest, testHandleTestSuiteEndSetsStatusOfRunningTestSuiteToGivenValue)
	{
		m_service->handleTestSuiteEnd(GetParam());
		ASSERT_EQ(GetParam(), m_runningTestSuite->getStatus());
	}

	namespace {
		std::vector<model::Status> testStatusData = { model::Status::BROKEN, model::Status::FAILED, model::Status::PASSED,
													  model::Status::SKIPPED, model::Status::UNKNOWN };
	}

	INSTANTIATE_TEST_SUITE_P(Test, TestSuiteEndEventHandlerStatusTest, ValuesIn(testStatusData));

}}}
