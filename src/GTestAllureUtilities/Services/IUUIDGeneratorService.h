#pragma once

#include <string>


namespace systelab { namespace gtest_allure_utilities { namespace service {

	class IUUIDGeneratorService
	{
	public:
		virtual ~IUUIDGeneratorService() = default;

		virtual std::string generateUUID() const = 0;
	};

}}}
