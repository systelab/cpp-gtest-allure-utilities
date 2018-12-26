#include "GTestAllureUtilities/Services/TestCaseJSONSerializer.h"

#include "GTestAllureUtilities/Model/TestCase.h"
#include "TestUtilities/JSONUtilities.h"

#include <gtest/gtest.h>


using namespace systelab::test_utility;
using namespace systelab::gtest_allure_utilities;

namespace systelab { namespace gtest_allure_utilities { namespace unit_test {

	class TestCaseJSONSerializerTest : public testing::Test
	{
	protected:
		service::TestCaseJSONSerializer m_service;
	};


	TEST_F(TestCaseJSONSerializerTest, testSerializeForTCWithoutActions)
	{
		model::TestCase testCase;
		testCase.setUUID("1bf09e3a-cdcf-4994-8718-5476636194f1");
		testCase.setHistoryId("66245a162d0fe05f10625e4c234eb8f0");
		testCase.setName("Test case name");
		testCase.setDescription("Description of the test case");
		testCase.setStatus(model::Status::PASSED);
		testCase.setStage(model::Stage::SCHEDULED);
		testCase.setStart(125);
		testCase.setStop(250);

		std::string expectedSerializedTestCase =
			"{\n"
			"    \"uuid\": \"1bf09e3a-cdcf-4994-8718-5476636194f1\",\n"
			"    \"historyId\": \"66245a162d0fe05f10625e4c234eb8f0\",\n"
			"    \"name\": \"Test case name\",\n"
			"    \"description\": \"Description of the test case\",\n"
			"    \"status\": \"passed\",\n"
			"    \"stage\": \"scheduled\",\n"
			"    \"start\": 125,\n"
			"    \"stop\": 250\n"
			"}";

		std::string serializedTestCase = m_service.serialize(testCase);
		ASSERT_TRUE(compareJSONs(expectedSerializedTestCase, serializedTestCase));
	}

}}}
