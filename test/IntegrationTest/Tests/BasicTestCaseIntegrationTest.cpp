#include "BaseIntegrationTest.h"

#include "TestUtilities/JSONUtilities.h"


using namespace testing;
using namespace systelab::test_utility;
using namespace systelab::gtest_allure;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class BasicTestCaseIntegrationTest : public testing::Test
									   , public BaseIntegrationTest
	{
	public:
		void SetUp()
		{
			BaseIntegrationTest::SetUp();
		}
	};


	TEST_F(BasicTestCaseIntegrationTest, testProgramWithSingleTestCase)
	{
		AllureAPI::setOutputFolder("IntegrationTest\\OutputFolder");
		AllureAPI::setTestSuiteName("SingleBasicTestCase");

		auto& listener = getEventListener();
		listener.onProgramStart();

		setCurrentTime(111);
		setNextUUIDToGenerate("12345678-1234-1234-1234-123456789012");
		listener.onTestStart("SingleTestCase");
		setCurrentTime(222);
		listener.onTestEnd(model::Status::PASSED);

		listener.onProgramEnd();

		ASSERT_EQ(1, getSavedFilesCount());
		StubFile savedFile = getSavedFile(0);
		ASSERT_EQ("IntegrationTest\\OutputFolder\\12345678-1234-1234-1234-123456789012-SingleBasicTestCase.json", savedFile.m_path);

		std::string expectedSavedFileContent =
			"{\n"
			"    \"uuid\": \"12345678-1234-1234-1234-123456789012\",\n"
			"    \"name\": \"SingleTestCase\",\n"
			"    \"status\": \"passed\",\n"
			"    \"stage\": \"finished\",\n"
			"    \"start\": 111,\n"
			"    \"stop\": 222\n"
			"}";

		ASSERT_TRUE(compareJSONs(expectedSavedFileContent, savedFile.m_content));
	}

	TEST_F(BasicTestCaseIntegrationTest, testProgramWithCoupleOfTestCases)
	{
		AllureAPI::setOutputFolder("IntegrationTest\\OutputFolder");
		AllureAPI::setTestSuiteName("CoupleOfBasicTestCases");

		auto& listener = getEventListener();
		listener.onProgramStart();

		setCurrentTime(101);
		setNextUUIDToGenerate("UUID1");
		listener.onTestStart("TestCase1");
		setCurrentTime(201);
		listener.onTestEnd(model::Status::FAILED);

		setCurrentTime(202);
		setNextUUIDToGenerate("UUID2");
		listener.onTestStart("TestCase2");
		setCurrentTime(301);
		listener.onTestEnd(model::Status::PASSED);

		listener.onProgramEnd();

		ASSERT_EQ(2, getSavedFilesCount());

		// First saved file
		StubFile firstSavedFile = getSavedFile(0);
		ASSERT_EQ("IntegrationTest\\OutputFolder\\UUID1-CoupleOfBasicTestCases.json", firstSavedFile.m_path);
		std::string expectedFirstSavedFileContent =
			"{\n"
			"    \"uuid\": \"UUID1\",\n"
			"    \"name\": \"TestCase1\",\n"
			"    \"status\": \"failed\",\n"
			"    \"stage\": \"finished\",\n"
			"    \"start\": 101,\n"
			"    \"stop\": 201\n"
			"}";
		ASSERT_TRUE(compareJSONs(expectedFirstSavedFileContent, firstSavedFile.m_content));

		// Second saved file
		StubFile secondSavedFile = getSavedFile(1);
		ASSERT_EQ("IntegrationTest\\OutputFolder\\UUID2-CoupleOfBasicTestCases.json", secondSavedFile.m_path);
		std::string expectedSecondSavedFileContent =
			"{\n"
			"    \"uuid\": \"UUID2\",\n"
			"    \"name\": \"TestCase2\",\n"
			"    \"status\": \"passed\",\n"
			"    \"stage\": \"finished\",\n"
			"    \"start\": 202,\n"
			"    \"stop\": 301\n"
			"}";
		ASSERT_TRUE(compareJSONs(expectedSecondSavedFileContent, secondSavedFile.m_content));
	}


}}}
