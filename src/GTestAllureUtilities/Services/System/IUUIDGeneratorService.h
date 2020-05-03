#pragma once

#include <string>


namespace systelab { namespace gtest_allure { namespace service {

	class IUUIDGeneratorService
	{
	public:
		virtual ~IUUIDGeneratorService() = default;

		virtual std::string generateUUID() const = 0;
	};

}}}
