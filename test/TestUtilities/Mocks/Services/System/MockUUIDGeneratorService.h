#pragma once

#include "GTestAllureUtilities/Services/System/IUUIDGeneratorService.h"


namespace systelab { namespace gtest_allure { namespace test_utility {

	class MockUUIDGeneratorService:  public service::IUUIDGeneratorService
	{
	public:
		MockUUIDGeneratorService();
		virtual ~MockUUIDGeneratorService();

		MOCK_CONST_METHOD0(generateUUID, std::string());
	};

}}}

