#pragma once

#include <string>


namespace systelab { namespace gtest_allure_utilities { namespace service {

	class IFileService
	{
	public:
		virtual ~IFileService() = default;

		virtual void saveFile(const std::string& filePath, const std::string& fileContent) const = 0;
	};

}}}
