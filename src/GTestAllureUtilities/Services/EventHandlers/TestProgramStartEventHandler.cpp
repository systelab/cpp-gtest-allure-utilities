#include "TestProgramStartEventHandler.h"

#include "Model/TestProgram.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestProgramStartEventHandler::TestProgramStartEventHandler(model::TestProgram& testProgram)
		:m_testProgram(testProgram)
	{
	}

	TestProgramStartEventHandler::~TestProgramStartEventHandler() = default;

	void TestProgramStartEventHandler::handleTestProgramStart() const
	{
		m_testProgram.clearTestSuites();
	}

}}}
