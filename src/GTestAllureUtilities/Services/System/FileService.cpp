#include "FileService.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>

#if defined(_WIN32)
#include <direct.h>
#endif


namespace systelab { namespace gtest_allure { namespace service {

	FileService::FileService()
	{
	}

	void FileService::saveFile(const std::string& filePath, const std::string& fileContent) const
	{
		createFileFolder(filePath);

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

	void FileService::createFileFolder(const std::string& filepath) const
	{
		auto filepathFragments = getPathFragments(filepath);

		unsigned int nFragments = (unsigned int) filepathFragments.size();
		if (nFragments > 1)
		{
			std::string folderPath = "";
			for (unsigned int i = 0; i < nFragments - 1; i++)
			{
				folderPath += (!folderPath.empty()) ? "/" : "";
				folderPath += filepathFragments[i];
				if (!folderExists(folderPath))
				{
					createFolder(folderPath);
				}
			}
		}
	}

	bool FileService::folderExists(const std::string& folderPath) const
	{
		struct stat info;
		if (stat(folderPath.c_str(), &info) != 0)
		{
			return 0;
		}
		else if (info.st_mode & S_IFDIR)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	std::vector<std::string> FileService::getPathFragments(const std::string& filepath) const
	{
		std::string cleanFilepath = filepath;
		std::replace(cleanFilepath.begin(), cleanFilepath.end(), '\\', '/');

		std::stringstream ss(cleanFilepath);
		std::string fragment;
		std::vector<std::string> fragments;
		while (std::getline(ss, fragment, '/'))
		{
			fragments.push_back(fragment);
		}

		return fragments;
	}

	std::string FileService::joinPath(std::vector<std::string>& pathFragments) const
	{
		std::ostringstream stream;
		for (const auto& fragment : pathFragments)
		{
			stream << (&fragment != &pathFragments[0]) ? "/" : "";
			stream << fragment;
		}

		return stream.str();
	}

	void FileService::createFolder(const std::string folderPath) const
	{
		int nError = 0;
#if defined(_WIN32)
		nError = _mkdir(folderPath.c_str());
#else 
		mode_t nMode = 0733;
		nError = mkdir(filePath.c_str(), nMode);
#endif
		if (nError != 0)
		{
			throw std::runtime_error("Unable to create folder exception: ");
		}
	}

}}}
