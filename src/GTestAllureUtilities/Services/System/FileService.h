#pragma once

#include "IFileService.h"

#include <vector>


namespace systelab { namespace gtest_allure { namespace service {

	class FileService : public IFileService
	{
	public:
		FileService();
		virtual ~FileService() = default;

		void saveFile(const std::string& filePath, const std::string& fileContent) const;

	private:
		void createFileFolder(const std::string& filePath) const;

		std::vector<std::string> getPathFragments(const std::string& filepath) const;
		std::string joinPath(std::vector<std::string>& pathFragments) const;

		bool folderExists(const std::string& folderPath) const;
		void createFolder(const std::string folderPath) const;
	};

}}}
