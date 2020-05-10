#include "stdafx.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestSuiteStartEventHandler.h"

#include "GTestAllureUtilities/Model/TestProgram.h"

#include "TestUtilities/Mocks/Services/System/MockTimeService.h"
#include "TestUtilities/Mocks/Services/System/MockUUIDGeneratorService.h"


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class TestSuiteStartEventHandlerTest : public testing::Test
	{
		void SetUp()
		{
			auto uuidGeneratorService = buildUUIDGeneratorService();
			auto timeService = buildTimeService();

			m_service = std::make_unique<service::TestSuiteStartEventHandler>(m_testProgram, std::move(uuidGeneratorService), std::move(timeService));
		}

		std::unique_ptr<service::IUUIDGeneratorService> buildUUIDGeneratorService()
		{
			auto uuidGeneratorService = std::make_unique<MockUUIDGeneratorService>();
			m_uuidGeneratorService = uuidGeneratorService.get();

			m_generatedUUID = "12345678-1234-1234-1234-123456789012";
			ON_CALL(*m_uuidGeneratorService, generateUUID()).WillByDefault(Return(m_generatedUUID));

			return uuidGeneratorService;
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
		std::unique_ptr<service::TestSuiteStartEventHandler> m_service;
		model::TestProgram m_testProgram;
		MockUUIDGeneratorService* m_uuidGeneratorService;
		MockTimeService* m_timeService;

		std::string m_generatedUUID;
		time_t m_currentTime;
	};


	TEST_F(TestSuiteStartEventHandlerTest, testHandleTestSuiteStartAddsStartedTestSuiteIntoProgram)
	{
		std::string startedTestSuiteName = "StartedTestSuite";
		m_service->handleTestSuiteStart(startedTestSuiteName);

		ASSERT_EQ(1, m_testProgram.getTestSuitesCount());

		model::TestSuite& addedTestSuite = m_testProgram.getTestSuite(0);
		EXPECT_EQ(startedTestSuiteName, addedTestSuite.getName());
		EXPECT_EQ(m_generatedUUID, addedTestSuite.getUUID());
		EXPECT_EQ(m_currentTime, addedTestSuite.getStart());
		EXPECT_EQ(model::Stage::RUNNING, addedTestSuite.getStage());
		EXPECT_EQ(model::Status::UNKNOWN, addedTestSuite.getStatus());
	}

}}}
