#include "TestSuiteJSONBuilder.h"

#include "Model/TestSuite.h"
#include "Services/Report/ITestCaseJSONSerializer.h"
#include "Services/System/IFileService.h"


namespace systelab { namespace gtest_allure_utilities { namespace service {

	TestSuiteJSONBuilder::TestSuiteJSONBuilder(std::unique_ptr<ITestCaseJSONSerializer> testCaseJSONSerializer,
											   std::unique_ptr<IFileService> fileService)
		:m_testCaseJSONSerializer(std::move(testCaseJSONSerializer))
		,m_fileService(std::move(fileService))
	{
	}

	void TestSuiteJSONBuilder::buildJSONFiles(const model::TestSuite& testSuite) const
	{
		size_t nTestCases = testSuite.getTestCasesCount();
		for (size_t i = 0; i < nTestCases; i++)
		{
			const model::TestCase& testCase = testSuite.getTestCase(i);
			std::string testCaseJSONFilepath = testSuite.getOutputFolder() + "\\" + testCase.getUUID() + "-" + testSuite.getName() + ".json";
			std::string testCaseJSONContent = m_testCaseJSONSerializer->serialize(testCase);
			m_fileService->saveFile(testCaseJSONFilepath, testCaseJSONContent);
		}
	}



}}}
