#include "TestProgramJSONBuilder.h"

#include "Model/TestProgram.h"
#include "Services/Report/ITestSuiteJSONSerializer.h"
#include "Services/System/IFileService.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestProgramJSONBuilder::TestProgramJSONBuilder(std::unique_ptr<ITestSuiteJSONSerializer> testSuiteJSONSerializer,
												   std::unique_ptr<IFileService> fileService)
		:m_testSuiteJSONSerializer(std::move(testSuiteJSONSerializer))
		,m_fileService(std::move(fileService))
	{
	}

	void TestProgramJSONBuilder::buildJSONFiles(const model::TestProgram& testProgram) const
	{
		std::string testProgramName = testProgram.getName();
		unsigned int nTestSuites = (unsigned int) testProgram.getTestSuitesCount();
		for (unsigned int i = 0; i < nTestSuites; i++)
		{
			const model::TestSuite& testSuite = testProgram.getTestSuite(i);
			std::string testCaseJSONFilepath = testProgram.getOutputFolder() + "\\" + testSuite.getUUID() + "-" + testProgramName + ".json";
			std::string testCaseJSONContent = m_testSuiteJSONSerializer->serialize(testSuite);
			m_fileService->saveFile(testCaseJSONFilepath, testCaseJSONContent);
		}
	}

}}}
