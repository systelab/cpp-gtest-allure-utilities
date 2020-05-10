#include "TestProgramEndEventHandler.h"

#include "Model/TestProgram.h"
#include "Services/Report/ITestProgramJSONBuilder.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestProgramEndEventHandler::TestProgramEndEventHandler(model::TestProgram& testProgram,
														   std::unique_ptr<ITestProgramJSONBuilder> testProgramJSONBuilderService)
		:m_testProgram(testProgram)
		,m_testProgramJSONBuilderService(std::move(testProgramJSONBuilderService))
	{
	}

	void TestProgramEndEventHandler::handleTestProgramEnd() const
	{
		m_testProgramJSONBuilderService->buildJSONFiles(m_testProgram);
	}

}}}
