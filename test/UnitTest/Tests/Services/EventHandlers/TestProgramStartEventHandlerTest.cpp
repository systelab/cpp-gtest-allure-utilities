#include "GTestAllureUtilities/Services/EventHandlers/TestProgramStartEventHandler.h"

#include "GTestAllureUtilities/Model/TestSuite.h"

#include <gtest/gtest.h>


using namespace testing;
using namespace systelab::gtest_allure;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class TestProgramStartEventHandlerTest : public testing::Test
	{
		void SetUp()
		{
			m_service = std::unique_ptr<service::TestProgramStartEventHandler>(new service::TestProgramStartEventHandler(m_testSuite) );
		}

	protected:
		std::unique_ptr<service::TestProgramStartEventHandler> m_service;
		model::TestSuite m_testSuite;
	};


	TEST_F(TestProgramStartEventHandlerTest, testHandleTestProgramStartClearsTestCasesOfTestSuite)
	{
		m_testSuite.addTestCase(model::TestCase());
		m_testSuite.addTestCase(model::TestCase());
		m_testSuite.addTestCase(model::TestCase());

		m_service->handleTestProgramStart();

		ASSERT_EQ(0, m_testSuite.getTestCasesCount());
	}

}}}
