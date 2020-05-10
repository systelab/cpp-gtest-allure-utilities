#include "stdafx.h"
#include "GTestAllureUtilities/Services/GoogleTest/GTestEventListener.h"

#include "TestUtilities/Mocks/Services/EventHandlers/MockTestCaseStartEventHandler.h"
#include "TestUtilities/Mocks/Services/EventHandlers/MockTestCaseEndEventHandler.h"
#include "TestUtilities/Mocks/Services/EventHandlers/MockTestProgramEndEventHandler.h"
#include "TestUtilities/Mocks/Services/EventHandlers/MockTestProgramStartEventHandler.h"
#include "TestUtilities/Mocks/Services/EventHandlers/MockTestSuiteEndEventHandler.h"
#include "TestUtilities/Mocks/Services/EventHandlers/MockTestSuiteStartEventHandler.h"


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class GTestEventListenerTest : public testing::Test
	{
	public:
		void SetUp()
		{
			auto testProgramStartEventHandler = buildTestProgramStartEventHandler();
			auto testSuiteStartEventHandler = buildTestSuiteStartEventHandler();
			auto testCaseStartEventHandler = buildTestCaseStartEventHandler();
			auto testCaseEndEventHandler = buildTestCaseEndEventHandler();
			auto testSuiteEndEventHandler = buildTestSuiteEndEventHandler();
			auto testProgramEndEventHandler = buildTestProgramEndEventHandler();

			m_listener = std::unique_ptr<service::GTestEventListener>(new service::GTestEventListener
							(std::move(testProgramStartEventHandler), std::move(testSuiteStartEventHandler),
							 std::move(testCaseStartEventHandler), std::move(testCaseEndEventHandler),
							 std::move(testSuiteEndEventHandler), std::move(testProgramEndEventHandler)));
		}

		std::unique_ptr<service::ITestProgramStartEventHandler> buildTestProgramStartEventHandler()
		{
			auto testProgramStartEventHandler = std::make_unique<MockTestProgramStartEventHandler>();
			m_testProgramStartEventHandler = testProgramStartEventHandler.get();
			return testProgramStartEventHandler;
		}

		std::unique_ptr<service::ITestSuiteStartEventHandler> buildTestSuiteStartEventHandler()
		{
			auto testSuiteStartEventHandler = std::make_unique<MockTestSuiteStartEventHandler>();
			m_testSuiteStartEventHandler = testSuiteStartEventHandler.get();
			return testSuiteStartEventHandler;
		}

		std::unique_ptr<service::ITestCaseStartEventHandler> buildTestCaseStartEventHandler()
		{
			auto testCaseStartEventHandler = std::unique_ptr<MockTestCaseStartEventHandler>(new MockTestCaseStartEventHandler());
			m_testCaseStartEventHandler = testCaseStartEventHandler.get();
			return testCaseStartEventHandler;
		}

		std::unique_ptr<service::ITestCaseEndEventHandler> buildTestCaseEndEventHandler()
		{
			auto testCaseEndEventHandler = std::unique_ptr<MockTestCaseEndEventHandler>(new MockTestCaseEndEventHandler());
			m_testCaseEndEventHandler = testCaseEndEventHandler.get();
			return testCaseEndEventHandler;
		}

		std::unique_ptr<service::ITestSuiteEndEventHandler> buildTestSuiteEndEventHandler()
		{
			auto testSuiteEndEventHandler = std::make_unique<MockTestSuiteEndEventHandler>();
			m_testSuiteEndEventHandler = testSuiteEndEventHandler.get();
			return testSuiteEndEventHandler;
		}

		std::unique_ptr<service::ITestProgramEndEventHandler> buildTestProgramEndEventHandler()
		{
			auto testProgramEndEventHandler = std::unique_ptr<MockTestProgramEndEventHandler>(new MockTestProgramEndEventHandler());
			m_testProgramEndEventHandler = testProgramEndEventHandler.get();
			return testProgramEndEventHandler;
		}

	protected:
		std::unique_ptr<service::GTestEventListener> m_listener;
		MockTestProgramStartEventHandler* m_testProgramStartEventHandler;
		MockTestSuiteStartEventHandler* m_testSuiteStartEventHandler;
		MockTestCaseStartEventHandler* m_testCaseStartEventHandler;
		MockTestCaseEndEventHandler* m_testCaseEndEventHandler;
		MockTestSuiteEndEventHandler* m_testSuiteEndEventHandler;
		MockTestProgramEndEventHandler* m_testProgramEndEventHandler;
	};


	TEST_F(GTestEventListenerTest, testOnTestProgramStartCallsTestCaseStartEventHandler)
	{
		EXPECT_CALL(*m_testProgramStartEventHandler, handleTestProgramStart());
		m_listener->OnTestProgramStart(*::testing::UnitTest::GetInstance());
	}

	TEST_F(GTestEventListenerTest, testOnTestSuiteStartCallsTestSuiteStartEventHandler)
	{
		EXPECT_CALL(*m_testSuiteStartEventHandler, handleTestSuiteStart("GTestEventListenerTest"));
		const ::testing::TestSuite* const testSuite = ::testing::UnitTest::GetInstance()->current_test_suite();
		m_listener->OnTestSuiteStart(*testSuite);
	}

	TEST_F(GTestEventListenerTest, testOnTestStartCallsTestCaseStartEventHandler)
	{
		EXPECT_CALL(*m_testCaseStartEventHandler, handleTestCaseStart("GTestEventListenerTest.testOnTestStartCallsTestCaseStartEventHandler"));
		const ::testing::TestInfo* const testInfo = ::testing::UnitTest::GetInstance()->current_test_info();
		m_listener->OnTestStart(*testInfo);
	}

	TEST_F(GTestEventListenerTest, testOnTestEndCallsTestCaseEndEventHandler)
	{
		EXPECT_CALL(*m_testCaseEndEventHandler, handleTestCaseEnd(model::Status::PASSED));
		const ::testing::TestInfo* const testInfo = ::testing::UnitTest::GetInstance()->current_test_info();
		m_listener->OnTestEnd(*testInfo);
	}

	TEST_F(GTestEventListenerTest, testOnTestSuiteEndCallsTestSuiteEndEventHandler)
	{
		EXPECT_CALL(*m_testSuiteEndEventHandler, handleTestSuiteEnd(model::Status::PASSED));
		const ::testing::TestSuite* const testSuite = ::testing::UnitTest::GetInstance()->current_test_suite();
		m_listener->OnTestSuiteEnd(*testSuite);
	}

	TEST_F(GTestEventListenerTest, testOnTestProgramEndCallsTestCaseEndEventHandler)
	{
		EXPECT_CALL(*m_testProgramEndEventHandler, handleTestProgramEnd());
		m_listener->OnTestProgramEnd(*::testing::UnitTest::GetInstance());
	}

}}}
