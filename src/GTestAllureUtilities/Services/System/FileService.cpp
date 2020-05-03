#include "FileService.h"

#include <fstream>


namespace systelab { namespace gtest_allure { namespace service {

	FileService::FileService()
	{
	}

	void FileService::saveFile(const std::string& filePath, const std::string& fileContent) const
	{
		try
		{
			std::ofstream outputFileStream;
			outputFileStream.exceptions(~std::ofstream::goodbit);
			outputFileStream.open(filePath);

			outputFileStream << fileContent;
			outputFileStream.close();
		}
		catch (std::ofstream::failure& exc)
		{
			throw UnableToWriteFileException(filePath, exc.what());
		}
	}

}}}
