#include "GTestAllureUtilities/Services/System/UUIDGeneratorService.h"

#include <gtest/gtest.h>


using namespace systelab::gtest_allure_utilities;

namespace systelab { namespace gtest_allure_utilities { namespace unit_test {

	class UUIDGeneratorServiceTest : public testing::Test
	{
	protected:
		bool isHexChar(char c)
		{
			return (c == '0') || (c == '1') || (c == '2') || (c == '3') ||
				   (c == '4') || (c == '5') || (c == '6') || (c == '7') ||
				   (c == '8') || (c == '9') || (c == 'a') || (c == 'b') ||
				   (c == 'c') || (c == 'd') || (c == 'e') || (c == 'f');
		}

	protected:
		service::UUIDGeneratorService m_service;
	};


	TEST_F(UUIDGeneratorServiceTest, testGenerateUUIDReturnsStringWithExpectedSize)
	{
		std::string generatedUUID = m_service.generateUUID();
		ASSERT_EQ(36, generatedUUID.size());
	}

	TEST_F(UUIDGeneratorServiceTest, testGenerateUUIDReturnsStringWithExpectedHyphens)
	{
		std::string generatedUUID = m_service.generateUUID();
		ASSERT_EQ(36, generatedUUID.size());
		EXPECT_EQ('-', generatedUUID[8]);
		EXPECT_EQ('-', generatedUUID[13]);
		EXPECT_EQ('-', generatedUUID[18]);
		EXPECT_EQ('-', generatedUUID[23]);
	}

	TEST_F(UUIDGeneratorServiceTest, testGenerateUUIDReturnsStringWithHexCharsForFirstFragment)
	{
		std::string generatedUUID = m_service.generateUUID();
		ASSERT_EQ(36, generatedUUID.size());
		EXPECT_TRUE(isHexChar(generatedUUID[0]));
		EXPECT_TRUE(isHexChar(generatedUUID[1]));
		EXPECT_TRUE(isHexChar(generatedUUID[2]));
		EXPECT_TRUE(isHexChar(generatedUUID[3]));
		EXPECT_TRUE(isHexChar(generatedUUID[4]));
		EXPECT_TRUE(isHexChar(generatedUUID[5]));
		EXPECT_TRUE(isHexChar(generatedUUID[6]));
		EXPECT_TRUE(isHexChar(generatedUUID[7]));
	}

	TEST_F(UUIDGeneratorServiceTest, testGenerateUUIDReturnsStringWithHexCharsForSecondFragment)
	{
		std::string generatedUUID = m_service.generateUUID();
		ASSERT_EQ(36, generatedUUID.size());
		EXPECT_TRUE(isHexChar(generatedUUID[9]));
		EXPECT_TRUE(isHexChar(generatedUUID[10]));
		EXPECT_TRUE(isHexChar(generatedUUID[11]));
		EXPECT_TRUE(isHexChar(generatedUUID[12]));
	}

	TEST_F(UUIDGeneratorServiceTest, testGenerateUUIDReturnsStringWithHexCharsForThirdFragment)
	{
		std::string generatedUUID = m_service.generateUUID();
		ASSERT_EQ(36, generatedUUID.size());
		EXPECT_TRUE(isHexChar(generatedUUID[14]));
		EXPECT_TRUE(isHexChar(generatedUUID[15]));
		EXPECT_TRUE(isHexChar(generatedUUID[16]));
		EXPECT_TRUE(isHexChar(generatedUUID[17]));
	}

	TEST_F(UUIDGeneratorServiceTest, testGenerateUUIDReturnsStringWithHexCharsForFourthFragment)
	{
		std::string generatedUUID = m_service.generateUUID();
		ASSERT_EQ(36, generatedUUID.size());
		EXPECT_TRUE(isHexChar(generatedUUID[19]));
		EXPECT_TRUE(isHexChar(generatedUUID[20]));
		EXPECT_TRUE(isHexChar(generatedUUID[21]));
		EXPECT_TRUE(isHexChar(generatedUUID[22]));
	}

	TEST_F(UUIDGeneratorServiceTest, testGenerateUUIDReturnsStringWithHexCharsForLastFragment)
	{
		std::string generatedUUID = m_service.generateUUID();
		ASSERT_EQ(36, generatedUUID.size());
		EXPECT_TRUE(isHexChar(generatedUUID[24]));
		EXPECT_TRUE(isHexChar(generatedUUID[25]));
		EXPECT_TRUE(isHexChar(generatedUUID[26]));
		EXPECT_TRUE(isHexChar(generatedUUID[27]));
		EXPECT_TRUE(isHexChar(generatedUUID[28]));
		EXPECT_TRUE(isHexChar(generatedUUID[29]));
		EXPECT_TRUE(isHexChar(generatedUUID[30]));
		EXPECT_TRUE(isHexChar(generatedUUID[31]));
		EXPECT_TRUE(isHexChar(generatedUUID[32]));
		EXPECT_TRUE(isHexChar(generatedUUID[33]));
		EXPECT_TRUE(isHexChar(generatedUUID[34]));
		EXPECT_TRUE(isHexChar(generatedUUID[35]));
	}

}}}
