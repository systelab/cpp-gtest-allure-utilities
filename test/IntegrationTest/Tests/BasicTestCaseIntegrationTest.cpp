#include "stdafx.h"
#include "BaseIntegrationTest.h"

#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"


using namespace testing;
using namespace systelab::json::test_utility;
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

		void TearDown()
		{
			BaseIntegrationTest::TearDown();
		}
	};


	TEST_F(BasicTestCaseIntegrationTest, testProgramWithSingleTestSuite)
	{
		AllureAPI::setOutputFolder("IntegrationTest\\OutputFolder");
		AllureAPI::setTestProgramName("TestProgramName");
		AllureAPI::setTMSLinksPattern("https://mytms.webpage.com/{}/refresh");

		auto& listener = getEventListener();
		listener.onProgramStart();

		setCurrentTime(111);
		setNextUUIDToGenerate("12345678-1234-1234-1234-123456789012");
		listener.onTestSuiteStart("SingleTestSuite");

		setCurrentTime(222);
		listener.onTestStart("SingleTestCase");

		setCurrentTime(333);
		listener.onTestEnd(model::Status::PASSED);

		setCurrentTime(444);
		listener.onTestSuiteEnd(model::Status::PASSED);

		listener.onProgramEnd();

		ASSERT_EQ(1, getSavedFilesCount());
		StubFile savedFile = getSavedFile(0);
		ASSERT_EQ("IntegrationTest\\OutputFolder\\12345678-1234-1234-1234-123456789012-TestProgramName.json", savedFile.m_path);

		std::string expectedSavedFileContent =
			"{\n"
			"    \"uuid\": \"12345678-1234-1234-1234-123456789012\",\n"
			"    \"name\": \"SingleTestSuite\",\n"
			"    \"status\": \"passed\",\n"
			"    \"stage\": \"finished\",\n"
			"    \"start\": 111,\n"
			"    \"stop\": 444,\n"
			"    \"labels\":\n"
			"    [\n"
			"        {\n"
			"            \"name\": \"suite\",\n"
			"            \"value\": \"SingleTestSuite\"\n"
			"        }\n"
			"    ],\n"
			"    \"links\":\n"
			"    [\n"
			"        {\n"
			"            \"name\": \"SingleTestSuite\",\n"
			"            \"url\": \"https://mytms.webpage.com/SingleTestSuite/refresh\",\n"
			"            \"type\": \"tms\"\n"
			"        }\n"
			"    ],\n"
			"    \"steps\":\n"
			"    [\n"
			"        {\n"
			"            \"name\": \"Action: SingleTestCase\",\n"
			"            \"status\": \"passed\",\n"
			"            \"stage\": \"finished\",\n"
			"            \"start\": 222,\n"
			"            \"stop\": 333\n"
			"        }\n"
			"    ]\n"
			"}";

		ASSERT_TRUE(compareJSONs(expectedSavedFileContent, savedFile.m_content, getJSONAdapter()));
	}

	TEST_F(BasicTestCaseIntegrationTest, testProgramWithCoupleOfTestSuites)
	{
		AllureAPI::setOutputFolder("IntegrationTest\\OutputFolder");
		AllureAPI::setTestProgramName("CoupleOfBasicTestSuites");
		AllureAPI::setTMSLinksPattern("http://{}");

		auto& listener = getEventListener();
		listener.onProgramStart();

		setCurrentTime(101);
		setNextUUIDToGenerate("UUID1");
		listener.onTestSuiteStart("TestSuite1");
		listener.onTestStart("TestCase1");
		setCurrentTime(201);
		listener.onTestEnd(model::Status::FAILED);
		listener.onTestSuiteEnd(model::Status::FAILED);

		setCurrentTime(301);
		setNextUUIDToGenerate("UUID2");
		listener.onTestSuiteStart("TestSuite2");
		listener.onTestStart("TestCase2.1");
		setCurrentTime(401);
		listener.onTestEnd(model::Status::PASSED);
		listener.onTestStart("TestCase2.2");
		setCurrentTime(501);
		listener.onTestEnd(model::Status::PASSED);
		listener.onTestStart("TestCase2.3");
		setCurrentTime(601);
		listener.onTestEnd(model::Status::SKIPPED);
		listener.onTestSuiteEnd(model::Status::PASSED);

		listener.onProgramEnd();

		ASSERT_EQ(2, getSavedFilesCount());

		// First saved file
		StubFile firstSavedFile = getSavedFile(0);
		ASSERT_EQ("IntegrationTest\\OutputFolder\\UUID1-CoupleOfBasicTestSuites.json", firstSavedFile.m_path);
		std::string expectedFirstSavedFileContent =
			"{\n"
			"    \"uuid\": \"UUID1\",\n"
			"    \"name\": \"TestSuite1\",\n"
			"    \"status\": \"failed\",\n"
			"    \"stage\": \"finished\",\n"
			"    \"start\": 101,\n"
			"    \"stop\": 201,\n"
			"    \"labels\":\n"
			"    [\n"
			"        {\n"
			"            \"name\": \"suite\",\n"
			"            \"value\": \"TestSuite1\"\n"
			"        }\n"
			"    ],\n"
			"    \"links\":\n"
			"    [\n"
			"        {\n"
			"            \"name\": \"TestSuite1\",\n"
			"            \"url\": \"http://TestSuite1\",\n"
			"            \"type\": \"tms\"\n"
			"        }\n"
			"    ],\n"
			"    \"steps\":\n"
			"    [\n"
			"        {\n"
			"            \"name\": \"Action: TestCase1\",\n"
			"            \"status\": \"failed\",\n"
			"            \"stage\": \"finished\",\n"
			"            \"start\": 101,\n"
			"            \"stop\": 201\n"
			"        }\n"
			"    ]\n"
			"}";
		ASSERT_TRUE(compareJSONs(expectedFirstSavedFileContent, firstSavedFile.m_content, getJSONAdapter()));

		// Second saved file
		StubFile secondSavedFile = getSavedFile(1);
		ASSERT_EQ("IntegrationTest\\OutputFolder\\UUID2-CoupleOfBasicTestSuites.json", secondSavedFile.m_path);
		std::string expectedSecondSavedFileContent =
			"{\n"
			"    \"uuid\": \"UUID2\",\n"
			"    \"name\": \"TestSuite2\",\n"
			"    \"status\": \"passed\",\n"
			"    \"stage\": \"finished\",\n"
			"    \"start\": 301,\n"
			"    \"stop\": 601,\n"
			"    \"labels\":\n"
			"    [\n"
			"        {\n"
			"            \"name\": \"suite\",\n"
			"            \"value\": \"TestSuite2\"\n"
			"        }\n"
			"    ],\n"
			"    \"links\":\n"
			"    [\n"
			"        {\n"
			"            \"name\": \"TestSuite2\",\n"
			"            \"url\": \"http://TestSuite2\",\n"
			"            \"type\": \"tms\"\n"
			"        }\n"
			"    ],\n"
			"    \"steps\":\n"
			"    [\n"
			"        {\n"
			"            \"name\": \"Action: TestCase2.1\",\n"
			"            \"status\": \"passed\",\n"
			"            \"stage\": \"finished\",\n"
			"            \"start\": 301,\n"
			"            \"stop\": 401\n"
			"        },\n"
			"        {\n"
			"            \"name\": \"Action: TestCase2.2\",\n"
			"            \"status\": \"passed\",\n"
			"            \"stage\": \"finished\",\n"
			"            \"start\": 401,\n"
			"            \"stop\": 501\n"
			"        },\n"
			"        {\n"
			"            \"name\": \"Action: TestCase2.3\",\n"
			"            \"status\": \"skipped\",\n"
			"            \"stage\": \"finished\",\n"
			"            \"start\": 501,\n"
			"            \"stop\": 601\n"
			"        }\n"
			"    ]\n"
			"}";
		ASSERT_TRUE(compareJSONs(expectedSecondSavedFileContent, secondSavedFile.m_content, getJSONAdapter()));
	}

	TEST_F(BasicTestCaseIntegrationTest, testProgramWithSingleComplexTestSuite)
	{
		AllureAPI::setOutputFolder("IntegrationTest\\OutputFolder");
		AllureAPI::setTestProgramName("ComplexTestProgram");
		AllureAPI::setTMSLinksPattern("https://mytms.webpage.com/{}/refresh");

		auto& listener = getEventListener();
		listener.onProgramStart();

		setCurrentTime(100);
		setNextUUIDToGenerate("UUID-Complex");
		listener.onTestSuiteStart("SingleComplexTestSuite");

		AllureAPI::setTMSId("UTILS-TC-0001");
		AllureAPI::setTestSuiteEpic("Complex Epic");
		AllureAPI::setTestSuiteName("MyComplexTestSuite");
		AllureAPI::setTestSuiteDescription("Description of complex test suite");
		AllureAPI::setTestSuiteSeverity("high");
		AllureAPI::setTestSuiteLabel("tag", "ThisIsMyTag");

		for (unsigned int i = 1; i <= 3; i++)
		{
			setCurrentTime(100 + (100 * i));
			listener.onTestStart("ParametricTest/" + std::to_string(i));

			AllureAPI::setTestCaseName("Description of action for scenario " + std::to_string(i));
			AllureAPI::addExpectedResult("Description of expectation for scenario " + std::to_string(i), [](){});

			setCurrentTime(190 + (100 * i));
			listener.onTestEnd(model::Status::PASSED);
		}

		setCurrentTime(500);
		listener.onTestSuiteEnd(model::Status::PASSED);

		listener.onProgramEnd();

		ASSERT_EQ(1, getSavedFilesCount());
		StubFile savedFile = getSavedFile(0);
		ASSERT_EQ("IntegrationTest\\OutputFolder\\UUID-Complex-ComplexTestProgram.json", savedFile.m_path);

		std::string expectedSavedFileContent =
			"{\n"
			"    \"uuid\": \"UUID-Complex\",\n"
			"    \"name\": \"MyComplexTestSuite\",\n"
			"    \"status\": \"passed\",\n"
			"    \"stage\": \"finished\",\n"
			"    \"start\": 100,\n"
			"    \"stop\": 500,\n"
			"    \"labels\":\n"
			"    [\n"
			"        {\n"
			"            \"name\": \"suite\",\n"
			"            \"value\": \"MyComplexTestSuite\"\n"
			"        },\n"
			"        {\n"
			"            \"name\": \"epic\",\n"
			"            \"value\": \"Complex Epic\"\n"
			"        },\n"
			"        {\n"
			"            \"name\": \"feature\",\n"
			"            \"value\": \"Description of complex test suite\"\n"
			"        },\n"
			"        {\n"
			"            \"name\": \"severity\",\n"
			"            \"value\": \"high\"\n"
			"        },\n"
			"        {\n"
			"            \"name\": \"tag\",\n"
			"            \"value\": \"ThisIsMyTag\"\n"
			"        }\n"
			"    ],\n"
			"    \"links\":\n"
			"    [\n"
			"        {\n"
			"            \"name\": \"UTILS-TC-0001\",\n"
			"            \"url\": \"https://mytms.webpage.com/UTILS-TC-0001/refresh\",\n"
			"            \"type\": \"tms\"\n"
			"        }\n"
			"    ],\n"
			"    \"steps\":\n"
			"    [\n"
			"        {\n"
			"            \"name\": \"Action: Description of action for scenario 1\",\n"
			"            \"status\": \"passed\",\n"
			"            \"stage\": \"finished\",\n"
			"            \"start\": 200,\n"
			"            \"stop\": 290,\n"
			"            \"steps\":\n"
			"            [\n"
			"                {\n"
			"                    \"name\": \"Description of expectation for scenario 1\",\n"
			"                    \"status\": \"passed\",\n"
			"                    \"stage\": \"finished\",\n"
			"                    \"start\": 200,\n"
			"                    \"stop\": 200\n"
			"                }\n"
			"            ]\n"
			"        },\n"
			"        {\n"
			"            \"name\": \"Action: Description of action for scenario 2\",\n"
			"            \"status\": \"passed\",\n"
			"            \"stage\": \"finished\",\n"
			"            \"start\": 300,\n"
			"            \"stop\": 390,\n"
			"            \"steps\":\n"
			"            [\n"
			"                {\n"
			"                    \"name\": \"Description of expectation for scenario 2\",\n"
			"                    \"status\": \"passed\",\n"
			"                    \"stage\": \"finished\",\n"
			"                    \"start\": 300,\n"
			"                    \"stop\": 300\n"
			"                }\n"
			"            ]\n"
			"        },\n"
			"        {\n"
			"            \"name\": \"Action: Description of action for scenario 3\",\n"
			"            \"status\": \"passed\",\n"
			"            \"stage\": \"finished\",\n"
			"            \"start\": 400,\n"
			"            \"stop\": 490,\n"
			"            \"steps\":\n"
			"            [\n"
			"                {\n"
			"                    \"name\": \"Description of expectation for scenario 3\",\n"
			"                    \"status\": \"passed\",\n"
			"                    \"stage\": \"finished\",\n"
			"                    \"start\": 400,\n"
			"                    \"stop\": 400\n"
			"                }\n"
			"            ]\n"
			"        }\n"
			"    ]\n"
			"}";

		ASSERT_TRUE(compareJSONs(expectedSavedFileContent, savedFile.m_content, getJSONAdapter()));
	}


}}}
