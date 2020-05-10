#include "stdafx.h"
#include "GTestAllureUtilities/Services/Report/TestProgramJSONBuilder.h"

#include "GTestAllureUtilities/Model/TestSuite.h"
#include "GTestAllureUtilities/Model/TestProgram.h"

#include "TestUtilities/Mocks/Services/System/MockFileService.h"
#include "TestUtilities/Mocks/Services/Report/MockTestSuiteJSONSerializer.h"


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;

namespace systelab { namespace gtest_allure_utilities { namespace unit_test {

	class TestProgramJSONBuilderTest : public testing::Test
	{
		void SetUp()
		{
			m_testProgram = buildTestProgram();

			auto testSuiteJSONSerializer = buildTestSuiteJSONSerializer();
			auto fileService = buildFileService();

			m_service = std::make_unique<service::TestProgramJSONBuilder>(std::move(testSuiteJSONSerializer), std::move(fileService));
		}

		std::unique_ptr<model::TestProgram> buildTestProgram()
		{
			m_testProgramName = "MyTestProgram";
			m_outputFolder = "TestProgramJSONBuilderTest\\Reports";
			m_testSuiteUUIDs = { "UUID1", "UUID2", "UUID3" };

			auto testProgram = std::make_unique<model::TestProgram>();
			testProgram->setName(m_testProgramName);

			for (auto& testSuiteUUID : m_testSuiteUUIDs)
			{
				model::TestSuite testSuite;
				testSuite.setUUID(testSuiteUUID);
				testProgram->addTestSuite(testSuite);
			}

			return testProgram;
		}

		std::unique_ptr<service::ITestSuiteJSONSerializer> buildTestSuiteJSONSerializer()
		{
			auto testSuiteJSONSerializer = std::make_unique<MockTestSuiteJSONSerializer>();
			m_testSuiteJSONSerializer = testSuiteJSONSerializer.get();

			ON_CALL(*m_testSuiteJSONSerializer, serialize(_)).WillByDefault(Invoke(
				[](const model::TestSuite& testSuite) -> std::string
				{
					return std::string("Serialized") + testSuite.getUUID();
				}
			));

			return testSuiteJSONSerializer;
		}

		std::unique_ptr<service::IFileService> buildFileService()
		{
			auto fileService = std::make_unique<MockFileService>();
			m_fileService = fileService.get();
			return fileService;
		}

	protected:
		std::unique_ptr<service::TestProgramJSONBuilder> m_service;
		MockTestSuiteJSONSerializer* m_testSuiteJSONSerializer;
		MockFileService* m_fileService;

		std::unique_ptr<model::TestProgram> m_testProgram;
		std::string m_testProgramName;
		std::string m_outputFolder;
		std::vector <std::string> m_testSuiteUUIDs;
	};


	TEST_F(TestProgramJSONBuilderTest, testBuildJSONFilesSavesAFileForEachTestCase)
	{
		for (const auto& testSuiteUUID : m_testSuiteUUIDs)
		{
			std::string expectedFilepath = m_outputFolder + "\\" + testSuiteUUID + "-" + m_testProgramName + ".json";
			std::string expectedFileContent = "Serialized" + testSuiteUUID;
			EXPECT_CALL(*m_fileService, saveFile(expectedFilepath, expectedFileContent));
		}

		m_service->buildJSONFiles(*m_testProgram);
	}

	TEST_F(TestProgramJSONBuilderTest, testBuildJSONFilesDoesNotSaveAFileWhenSuiteHasNoTestCases)
	{
		EXPECT_CALL(*m_fileService, saveFile(_, _)).Times(0);

		model::TestProgram emptyTestProgram;
		m_service->buildJSONFiles(emptyTestProgram);
	}

}}}
