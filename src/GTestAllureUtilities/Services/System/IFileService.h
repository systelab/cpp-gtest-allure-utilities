#pragma once

#include <stdexcept>
#include <string>


namespace systelab { namespace gtest_allure { namespace service {

	class IFileService
	{
	public:
		virtual ~IFileService() = default;

		virtual void saveFile(const std::string& filePath, const std::string& fileContent) const = 0;

	public:
		struct UnableToWriteFileException : std::runtime_error
		{
			UnableToWriteFileException(const std::string& filepath,
									   const std::string& detailedError)
				:std::runtime_error("Unable to write file to disk")
				,m_filepath(filepath)
				,m_detailedError(detailedError)
			{}

			std::string m_filepath;
			std::string m_detailedError;
		};
	};

}}}
