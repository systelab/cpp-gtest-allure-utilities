#include "UUIDGeneratorService.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>


namespace systelab { namespace gtest_allure_utilities { namespace service {

	UUIDGeneratorService::UUIDGeneratorService()
	{
	}

	std::string UUIDGeneratorService::generateUUID() const
	{
		std::ostringstream oss;

		bool first = true;
		std::vector<unsigned int> itemsLength = { 4, 2, 2, 2, 6 };
		for (auto itemLength : itemsLength)
		{
			oss << (first ? generateHex(itemLength) : '-' + generateHex(itemLength));
			first = false;
		}

		return oss.str();
	}

	std::string UUIDGeneratorService::generateHex(unsigned int length) const
	{
		std::ostringstream oss;
		for (unsigned int i = 0; i < length; i++)
		{
			unsigned char randomChar = generateRandomChar();
			std::stringstream hexStream;
			hexStream << std::hex << int(randomChar);
			std::string hexChar = hexStream.str();
			oss << (hexChar.length() < 2 ? '0' + hexChar : hexChar);
		}

		return oss.str();
	}

	unsigned char UUIDGeneratorService::generateRandomChar() const
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 255);
		return static_cast<unsigned char>(dis(gen));
	}

}}}
