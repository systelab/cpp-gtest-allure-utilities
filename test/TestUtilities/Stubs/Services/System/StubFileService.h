#pragma once

#include "TestUtilities/Mocks/Services/System/MockFileService.h"



namespace systelab { namespace gtest_allure { namespace test_utility {

	struct StubFile
	{
		std::string m_path;
		std::string m_content;
	};

	class StubFileService:  public MockFileService
	{
	public:
		StubFileService(std::vector<StubFile>&);
		virtual ~StubFileService();

		void saveFileStub(const std::string& filePath, const std::string& fileContent) const;

	private:
		std::vector<StubFile>& m_filesSaved;
	};

}}}

