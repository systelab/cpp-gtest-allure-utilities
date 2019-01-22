#include "GTestAllureUtilities/Services/System/FileService.h"

#include <memory>
#include <fstream>
#include <gtest/gtest.h>


using namespace systelab::gtest_allure_utilities;

namespace systelab { namespace gtest_allure_utilities { namespace unit_test {

	class FileServiceTest : public testing::Test
	{
		void SetUp()
		{
			m_testFilepath = "FileServiceTest.txt";
			remove(m_testFilepath.c_str());
		}

		void TearDown()
		{
			remove(m_testFilepath.c_str());
		}

	protected:
		std::unique_ptr<std::string> readFile(std::string& filepath)
		{
			std::ifstream fileStream(filepath);
			if (!fileStream.good())
			{
				return std::unique_ptr<std::string>();
			}

			std::stringstream buffer;
			buffer << fileStream.rdbuf();
			std::string content = buffer.str();

			return std::unique_ptr<std::string>(new std::string(content));
		}

	protected:
		service::FileService m_service;
		std::string m_testFilepath;
	};


	TEST_F(FileServiceTest, testSaveFileWritesGivenContentIntoGivenFilepath)
	{
		std::string expectedFileContent = "This is the test content to write";
		m_service.saveFile(m_testFilepath, expectedFileContent);

		std::unique_ptr<std::string> fileContent = readFile(m_testFilepath);
		ASSERT_TRUE(fileContent != NULL);
		ASSERT_EQ(expectedFileContent, *fileContent);
	}

	TEST_F(FileServiceTest, testSaveFileThrowsExceptionWhenUnableToWriteIntoFile)
	{
		std::string invalidFileName = "<|?s/>";
		ASSERT_THROW(m_service.saveFile(invalidFileName, "TestContent"), service::IFileService::UnableToWriteFileException);
	}

}}}
