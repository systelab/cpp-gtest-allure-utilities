#include "StubFileService.h"


using namespace testing;

namespace systelab { namespace gtest_allure { namespace test_utility {

	StubFileService::StubFileService(std::vector<StubFile>& filesSaved)
		:m_filesSaved(filesSaved)
	{
		ON_CALL(*this, saveFile(_, _)).WillByDefault(Invoke(this, &StubFileService::saveFileStub));
	}

	StubFileService::~StubFileService()
	{
	}

	void StubFileService::saveFileStub(const std::string& filePath, const std::string& fileContent) const
	{
		StubFile newSavedFile;
		newSavedFile.m_path = filePath;
		newSavedFile.m_content = fileContent;
		m_filesSaved.push_back(newSavedFile);
	}

}}}

