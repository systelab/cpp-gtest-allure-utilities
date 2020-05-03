#pragma once

#include "IUUIDGeneratorService.h"


namespace systelab { namespace gtest_allure { namespace service {

	class UUIDGeneratorService : public IUUIDGeneratorService
	{
	public:
		UUIDGeneratorService();
		virtual ~UUIDGeneratorService() = default;

		std::string generateUUID() const;

	private:
		std::string generateHex(unsigned int length) const;
		unsigned char generateRandomChar() const;
	};

}}}
