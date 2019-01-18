#include "FileService.h"

#include <fstream>


namespace systelab { namespace gtest_allure_utilities { namespace service {

	FileService::FileService()
	{
	}

	void FileService::saveFile(const std::string& filePath, const std::string& fileContent) const
	{
		std::ofstream ofs(filePath);
		ofs << fileContent;
		ofs.close();
	}

}}}
