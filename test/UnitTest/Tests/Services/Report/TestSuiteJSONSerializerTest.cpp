#include "stdafx.h"
#include "GTestAllureUtilities/Services/Report/TestSuiteJSONSerializer.h"

#include "GTestAllureUtilities/Model/Action.h"
#include "GTestAllureUtilities/Model/ExpectedResult.h"
#include "GTestAllureUtilities/Model/TestSuite.h"

#include "RapidJSONAdapter/JSONAdapter.h"
#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"


using namespace testing;
using namespace systelab::json::test_utility;
using namespace systelab::gtest_allure;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class TestSuiteJSONSerializerTest : public Test
	{
	public:
		void SetUp()
		{
			auto jsonAdapter = std::make_unique<systelab::json::rapidjson::JSONAdapter>();
			m_service = std::make_unique<service::TestSuiteJSONSerializer>(std::move(jsonAdapter));
		}

	protected:
		std::unique_ptr<service::TestSuiteJSONSerializer> m_service;
		systelab::json::rapidjson::JSONAdapter m_jsonAdapter;
	};


	TEST_F(TestSuiteJSONSerializerTest, testSerializeForTCWithoutActions)
	{
		model::TestSuite testSuite;
		testSuite.setUUID("1bf09e3a-cdcf-4994-8718-5476636194f1");
		testSuite.setName("Test suite name");
		testSuite.setStatus(model::Status::PASSED);
		testSuite.setStage(model::Stage::SCHEDULED);
		testSuite.setStart(125);
		testSuite.setStop(250);

		std::string expectedSerializedTestSuite =
			"{\n"
			"    \"uuid\": \"1bf09e3a-cdcf-4994-8718-5476636194f1\",\n"
			"    \"name\": \"Test suite name\",\n"
			"    \"status\": \"passed\",\n"
			"    \"stage\": \"scheduled\",\n"
			"    \"start\": 125,\n"
			"    \"stop\": 250,\n"
			"    \"labels\": [\n"
			"         { \"name\": \"suite\", \"value\": \"Test suite name\"}"
			"    ]\n"
			"}";

		std::string serializedTestSuite = m_service->serialize(testSuite);
		ASSERT_TRUE(compareJSONs(expectedSerializedTestSuite, serializedTestSuite, m_jsonAdapter));
	}

	TEST_F(TestSuiteJSONSerializerTest, testSerializeForTCWithLinksAndLabels)
	{
		model::TestSuite testSuite;
		testSuite.setUUID("A9C297DD-7138-4E78-AF70-0C1B2511E76E");
		testSuite.setName("Test suite with links and labels");
		testSuite.setStatus(model::Status::SKIPPED);
		testSuite.setStage(model::Stage::PENDING);
		testSuite.setStart(111);
		testSuite.setStop(222);

		model::Link link1;
		link1.setName("TC link 1");
		link1.setURL("http://www.mylink1.com");
		link1.setType("tms");
		testSuite.addLink(link1);

		model::Link link2;
		link2.setName("TC link 2");
		link2.setURL("http://www.jama.com/link");
		link2.setType("jama");
		testSuite.addLink(link2);

		model::Label label1;
		label1.setName("package");
		label1.setValue("UnitTest");
		testSuite.addLabel(label1);

		model::Label label2;
		label2.setName("feature");
		label2.setValue("TestSuiteJSONSerializer");
		testSuite.addLabel(label2);

		std::string expectedSerializedTestSuite =
			"{\n"
			"    \"uuid\": \"A9C297DD-7138-4E78-AF70-0C1B2511E76E\",\n"
			"    \"name\": \"Test suite with links and labels\",\n"
			"    \"status\": \"skipped\",\n"
			"    \"stage\": \"pending\",\n"
			"    \"start\": 111,\n"
			"    \"stop\": 222,\n"
			"    \"links\": [\n"
			"        {\n"
			"            \"name\": \"TC link 1\",\n"
			"            \"url\": \"http://www.mylink1.com\",\n"
			"            \"type\": \"tms\"\n"
			"        },\n"
			"        {\n"
			"            \"name\": \"TC link 2\",\n"
			"            \"url\": \"http://www.jama.com/link\",\n"
			"            \"type\": \"jama\"\n"
			"        }\n"
			"    ],\n"
			"    \"labels\": [\n"
			"        {\n"
			"            \"name\": \"suite\",\n"
			"            \"value\": \"Test suite with links and labels\"\n"
			"        },\n"
			"        {\n"
			"            \"name\": \"package\",\n"
			"            \"value\": \"UnitTest\"\n"
			"        },\n"
			"        {\n"
			"            \"name\": \"feature\",\n"
			"            \"value\": \"TestSuiteJSONSerializer\"\n"
			"        }\n"
			"    ]\n"
			"}";

		std::string serializedTestSuite = m_service->serialize(testSuite);
		ASSERT_TRUE(compareJSONs(expectedSerializedTestSuite, serializedTestSuite, m_jsonAdapter));
	}

	TEST_F(TestSuiteJSONSerializerTest, testSerializeForTCWithSingleActionAndExpectedResult)
	{
		model::TestSuite testSuite;
		testSuite.setUUID("3E43CDC5-0839-4ABB-8ED2-BE669F89D512");
		testSuite.setName("Test suite with single test case");
		testSuite.setStatus(model::Status::FAILED);
		testSuite.setStage(model::Stage::FINISHED);
		testSuite.setStart(123456);
		testSuite.setStop(789012);

		model::TestCase testCase;
		testCase.setName("Test case with single action");
		testCase.setStatus(model::Status::BROKEN);
		testCase.setStage(model::Stage::INTERRUPTED);
		testCase.setStart(124000);
		testCase.setStop(789000);

		auto action = std::make_unique<model::Action>();
		action->setName("Execute algorithm");
		action->setStatus(model::Status::PASSED);
		action->setStage(model::Stage::FINISHED);
		action->setStart(125000);
		action->setStop(126000);
		testCase.addStep(std::move(action));

		auto expectedResult = std::make_unique<model::ExpectedResult>();
		expectedResult->setName("Algorithm result is 10");
		expectedResult->setStatus(model::Status::UNKNOWN);
		expectedResult->setStage(model::Stage::RUNNING);
		expectedResult->setStart(126000);
		expectedResult->setStop(127000);
		testCase.addStep(std::move(expectedResult));

		testSuite.addTestCase(testCase);

		std::string expectedSerializedTestSuite =
			"{\n"
			"    \"uuid\": \"3E43CDC5-0839-4ABB-8ED2-BE669F89D512\",\n"
			"    \"name\": \"Test suite with single test case\",\n"
			"    \"status\": \"failed\",\n"
			"    \"stage\": \"finished\",\n"
			"    \"start\": 123456,\n"
			"    \"stop\": 789012,\n"
			"    \"labels\": [\n"
			"         { \"name\": \"suite\", \"value\": \"Test suite with single test case\"}"
			"    ],\n"
			"    \"steps\":\n"
			"    ["
			"        {\n"
			"            \"name\": \"Action: Test case with single action\",\n"
			"            \"status\": \"broken\",\n"
			"            \"stage\": \"interrupted\",\n"
			"            \"start\": 124000,\n"
			"            \"stop\": 789000,\n"
			"            \"steps\":\n"
			"            [\n"
			"                {\n"
			"                     \"name\": \"Action: Execute algorithm\",\n"
			"                     \"status\": \"passed\",\n"
			"                     \"stage\": \"finished\",\n"
			"                     \"start\": 125000,\n"
			"                     \"stop\": 126000\n"
			"                },\n"
			"                {\n"
			"                    \"name\": \"Algorithm result is 10\",\n"
			"                    \"status\": \"unknown\",\n"
			"                    \"stage\": \"running\",\n"
			"                    \"start\": 126000,\n"
			"                    \"stop\": 127000\n"
			"                }\n"
			"            ]\n"
			"        }\n"
			"    ]\n"
			"}";

		std::string serializedTestSuite = m_service->serialize(testSuite);
		ASSERT_TRUE(compareJSONs(expectedSerializedTestSuite, serializedTestSuite, m_jsonAdapter));
	}

}}}
