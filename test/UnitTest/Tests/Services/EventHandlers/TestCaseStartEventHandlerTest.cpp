#include "stdafx.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestCaseStartEventHandler.h"

#include "GTestAllureUtilities/Model/TestProgram.h"

#include "TestUtilities/Mocks/Services/System/MockTimeService.h"
#include "TestUtilities/Mocks/Services/System/MockUUIDGeneratorService.h"


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class TestCaseStartEventHandlerTest : public testing::Test
	{
		void SetUp()
		{
			m_testProgram = buildTestProgram();
			auto timeService = buildTimeService();

			m_service = std::make_unique<service::TestCaseStartEventHandler>(m_testProgram, std::move(timeService));
		}

		model::TestProgram buildTestProgram()
		{
			model::TestProgram testProgram;

			return testProgram;
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
		std::unique_ptr<service::TestCaseStartEventHandler> m_service;
		model::TestProgram m_testProgram;
		MockUUIDGeneratorService* m_uuidGeneratorService;
		MockTimeService* m_timeService;

		std::string m_generatedUUID;
		time_t m_currentTime;
	};


	//TEST_F(TestCaseStartEventHandlerTest, testHandleTestCaseStartAddsStartedTestCaseIntoSuite)
	//{
	//	std::string startedTestCaseName = "StartedTestCase";
	//	m_service->handleTestCaseStart(startedTestCaseName);

	//	ASSERT_EQ(1, m_testSuite.getTestCasesCount());

	//	model::TestCase& addedTestCase = m_testSuite.getTestCase(0);
	//	EXPECT_EQ(startedTestCaseName, addedTestCase.getName());
	//	EXPECT_EQ(m_generatedUUID, addedTestCase.getUUID());
	//	EXPECT_EQ(m_currentTime, addedTestCase.getStart());
	//	EXPECT_EQ(model::Stage::RUNNING, addedTestCase.getStage());
	//	EXPECT_EQ(model::Status::UNKNOWN, addedTestCase.getStatus());
	//}

}}}
