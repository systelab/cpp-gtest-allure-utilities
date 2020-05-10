#include "stdafx.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestProgramStartEventHandler.h"

#include "GTestAllureUtilities/Model/TestProgram.h"


using namespace testing;
using namespace systelab::gtest_allure;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class TestProgramStartEventHandlerTest : public testing::Test
	{
		void SetUp()
		{
			m_service = std::unique_ptr<service::TestProgramStartEventHandler>(new service::TestProgramStartEventHandler(m_testProgram) );
		}

	protected:
		std::unique_ptr<service::TestProgramStartEventHandler> m_service;
		model::TestProgram m_testProgram;
	};


	TEST_F(TestProgramStartEventHandlerTest, testHandleTestProgramStartClearsTestCasesOfTestSuite)
	{
		m_testProgram.addTestSuite(model::TestSuite());
		m_testProgram.addTestSuite(model::TestSuite());
		m_testProgram.addTestSuite(model::TestSuite());

		m_service->handleTestProgramStart();

		ASSERT_EQ(0, m_testProgram.getTestSuitesCount());
	}

}}}
