#include "TestCaseStartEventHandler.h"

#include "Model/TestSuite.h"
#include "Services/IFileService.h"
#include "Services/ITestCaseJSONSerializer.h"

#include "Model/TestSuite.h"
#include "Services/IUUIDGeneratorService.h"


namespace systelab { namespace gtest_allure_utilities { namespace service {

	TestCaseStartEventHandler::TestCaseStartEventHandler(model::TestSuite& testSuite,
														 std::unique_ptr<IUUIDGeneratorService> uuidGeneratorService)
		:m_testSuite(testSuite)
		,m_uuidGeneratorService(std::move(uuidGeneratorService))
	{
	}

	void TestCaseStartEventHandler::handleTestCaseStart(const std::string& testCaseName) const
	{
		model::TestCase testCase;
		testCase.setName(testCaseName);
		testCase.setUUID(m_uuidGeneratorService->generateUUID());
		m_testSuite.addTestCase(testCase);
	}

}}}
