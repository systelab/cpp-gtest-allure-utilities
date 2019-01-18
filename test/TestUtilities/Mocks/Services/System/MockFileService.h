#pragma once

#include "GTestAllureUtilities/Services/System/IFileService.h"

#include <gmock/gmock.h>


namespace systelab { namespace gtest_allure_utilities { namespace test_utility {

	class MockFileService:  public service::IFileService
	{
	public:
		MockFileService();
		virtual ~MockFileService();

		MOCK_CONST_METHOD2(saveFile, void(const std::string&, const std::string&));
	};

}}}

