#include "stdafx.h"
#include "GTestAllureUtilities/Services/Report/TestSuiteJSONBuilder.h"

#include "GTestAllureUtilities/Model/TestSuite.h"

#include "TestUtilities/Mocks/Services/System/MockFileService.h"
#include "TestUtilities/Mocks/Services/Report/MockTestCaseJSONSerializer.h"


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;

namespace systelab { namespace gtest_allure_utilities { namespace unit_test {

	class TestSuiteJSONBuilderTest : public testing::Test
	{
		void SetUp()
		{
			m_testSuite = buildTestSuite();

			auto testCaseJSONSerializer = buildTestCaseJSONSerializer();
			auto fileService = buildFileService();

			m_service = std::unique_ptr<service::TestSuiteJSONBuilder>(new service::TestSuiteJSONBuilder(
							std::move(testCaseJSONSerializer), std::move(fileService) ));
		}

		std::unique_ptr<model::TestSuite> buildTestSuite()
		{
			m_testSuiteName = "MyTestSuite";
			m_outputFolder = "TestSuiteJSONBuilderTest\\Reports";
			m_testCaseUUIDs = { "UUID1", "UUID2", "UUID3" };

			auto testSuite = std::unique_ptr<model::TestSuite>(new model::TestSuite());
			testSuite->setName(m_testSuiteName);
			testSuite->setOutputFolder(m_outputFolder);

			for (auto& testCaseUUID : m_testCaseUUIDs)
			{
				model::TestCase testCase;
				testCase.setUUID(testCaseUUID);
				testSuite->addTestCase(testCase);
			}

			return testSuite;
		}

		std::unique_ptr<service::ITestCaseJSONSerializer> buildTestCaseJSONSerializer()
		{
			auto testCaseJSONSerializer = std::unique_ptr<MockTestCaseJSONSerializer>(new MockTestCaseJSONSerializer());
			m_testCaseJSONSerializer = testCaseJSONSerializer.get();

			ON_CALL(*m_testCaseJSONSerializer, serialize(_)).WillByDefault(Invoke(
				[](const model::TestCase& testCase) -> std::string
				{
					return std::string("Serialized") + testCase.getUUID();
				}
			));

			return testCaseJSONSerializer;
		}

		std::unique_ptr<service::IFileService> buildFileService()
		{
			auto fileService = std::unique_ptr<MockFileService>(new MockFileService());
			m_fileService = fileService.get();
			return fileService;
		}

	protected:
		std::unique_ptr<service::TestSuiteJSONBuilder> m_service;
		MockTestCaseJSONSerializer* m_testCaseJSONSerializer;
		MockFileService* m_fileService;

		std::unique_ptr<model::TestSuite> m_testSuite;
		std::string m_testSuiteName;
		std::string m_outputFolder;
		std::vector <std::string> m_testCaseUUIDs;
	};


	TEST_F(TestSuiteJSONBuilderTest, testBuildJSONFilesSavesAFileForEachTestCase)
	{
		for (const auto& testCaseUUID : m_testCaseUUIDs)
		{
			std::string expectedFilepath = m_outputFolder + "\\" + testCaseUUID + "-" + m_testSuiteName + ".json";
			std::string expectedFileContent = "Serialized" + testCaseUUID;
			EXPECT_CALL(*m_fileService, saveFile(expectedFilepath, expectedFileContent));
		}

		m_service->buildJSONFiles(*m_testSuite);
	}

	TEST_F(TestSuiteJSONBuilderTest, testBuildJSONFilesDoesNotSaveAFileWhenSuiteHasNoTestCases)
	{
		EXPECT_CALL(*m_fileService, saveFile(_, _)).Times(0);

		model::TestSuite emptyTestSuite;
		m_service->buildJSONFiles(emptyTestSuite);
	}


}}}
