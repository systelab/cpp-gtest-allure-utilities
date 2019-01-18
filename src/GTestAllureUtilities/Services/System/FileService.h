#pragma once

#include "IFileService.h"


namespace systelab { namespace gtest_allure_utilities { namespace service {

	class FileService : public IFileService
	{
	public:
		FileService();
		virtual ~FileService() = default;

		void saveFile(const std::string& filePath, const std::string& fileContent) const;
	};

}}}
