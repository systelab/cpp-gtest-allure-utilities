#include "GTestAllureUtilities/Services/Report/TestSuiteJSONBuilder.h"

#include "GTestAllureUtilities/Model/TestSuite.h"

#include "TestUtilities/Mocks/Services/System/MockFileService.h"
#include "TestUtilities/Mocks/Services/Report/MockTestCaseJSONSerializer.h"

#include <gtest/gtest.h>


using namespace testing;
using namespace systelab::gtest_allure_utilities;
using namespace systelab::gtest_allure_utilities::test_utility;

namespace systelab { namespace gtest_allure_utilities { namespace unit_test {

	class TestSuiteJSONBuilderTest : public testing::Test
	{
		void SetUp()
		{
			auto testSuite = buildTestSuite();
			auto testCaseJSONSerializer = buildTestCaseJSONSerializer();
			auto fileService = buildFileService();

			m_service = std::make_unique<service::TestSuiteJSONBuilder>
							(std::move(testCaseJSONSerializer), std::move(fileService));
		}

		std::unique_ptr<model::TestSuite> buildTestSuite()
		{
			auto testSuite = std::make_unique<model::TestSuite>();

			model::TestCase testCase1;
			testCase1.setName("Test Case 1");
			testSuite->addTestCase(testCase1);

			model::TestCase testCase2;
			testCase2.setName("Test Case 2");
			testSuite->addTestCase(testCase2);

			model::TestCase testCase3;
			testCase3.setName("Test Case 3");
			testSuite->addTestCase(testCase3);

			return testSuite;
		}

		std::unique_ptr<service::ITestCaseJSONSerializer> buildTestCaseJSONSerializer()
		{
			auto testCaseJSONSerializer = std::make_unique<MockTestCaseJSONSerializer>();
			m_testCaseJSONSerializer = testCaseJSONSerializer.get();

			ON_CALL(*m_testCaseJSONSerializer, serialize(_)).WillByDefault(Invoke(
				[](const model::TestCase& testCase) -> std::string
				{
					return std::string("Serialized") + testCase.getName();
				}
			));

			return testCaseJSONSerializer;
		}

		std::unique_ptr<service::IFileService> buildFileService()
		{
			auto fileService = std::make_unique<MockFileService>();
			m_fileService = fileService.get();
			return fileService;
		}

	protected:
		std::unique_ptr<service::TestSuiteJSONBuilder> m_service;
		MockTestCaseJSONSerializer* m_testCaseJSONSerializer;
		MockFileService* m_fileService;
		
		model::TestSuite* m_testSuite;
	};


	TEST_F(TestSuiteJSONBuilderTest, test)
	{
		//ON_CALL(*m_fileService, )
	}

}}}
