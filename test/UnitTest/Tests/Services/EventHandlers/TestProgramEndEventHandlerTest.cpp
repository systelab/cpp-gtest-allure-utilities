#include "GTestAllureUtilities/Services/EventHandlers/TestProgramEndEventHandler.h"

#include "GTestAllureUtilities/Model/TestSuite.h"

#include "TestUtilities/Mocks/Services/Report/MockTestSuiteJSONBuilder.h"

#include <gtest/gtest.h>


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;

namespace systelab { namespace gtest_allure_utilities { namespace unit_test {

	class TestProgramEndEventHandlerTest : public testing::Test
	{
		void SetUp()
		{
			auto testSuiteJSONBuilder = buildTestSuiteJSONBuilder();

			m_service = std::unique_ptr<service::TestProgramEndEventHandler>(new service::TestProgramEndEventHandler
							(m_testSuite, std::move(testSuiteJSONBuilder)) );
		}

		std::unique_ptr<service::ITestSuiteJSONBuilder> buildTestSuiteJSONBuilder()
		{
			auto testSuiteJSONBuilder = std::unique_ptr<MockTestSuiteJSONBuilder>(new MockTestSuiteJSONBuilder());
			m_testSuiteJSONBuilder = testSuiteJSONBuilder.get();
			return testSuiteJSONBuilder;
		}

	protected:
		std::unique_ptr<service::TestProgramEndEventHandler> m_service;
		model::TestSuite m_testSuite;
		MockTestSuiteJSONBuilder* m_testSuiteJSONBuilder;
	};


	TEST_F(TestProgramEndEventHandlerTest, testHandleTestProgramEndBuildsTestSuiteJSONs)
	{
		EXPECT_CALL(*m_testSuiteJSONBuilder, buildJSONFiles(m_testSuite));
		m_service->handleTestProgramEnd();
	}

}}}
