#include "TestProgramStartEventHandler.h"

#include "Model/TestSuite.h"


namespace systelab { namespace gtest_allure_utilities { namespace service {

	TestProgramStartEventHandler::TestProgramStartEventHandler(model::TestSuite& testSuite)
		:m_testSuite(testSuite)
	{
	}

	void TestProgramStartEventHandler::handleTestProgramStart() const
	{
		m_testSuite.clearTestCases();
	}

}}}
