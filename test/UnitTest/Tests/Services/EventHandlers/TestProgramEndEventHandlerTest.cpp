#include "stdafx.h"
#include "GTestAllureUtilities/Services/EventHandlers/TestProgramEndEventHandler.h"

#include "GTestAllureUtilities/Model/TestProgram.h"

#include "TestUtilities/Mocks/Services/Report/MockTestProgramJSONBuilder.h"


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;

namespace systelab { namespace gtest_allure_utilities { namespace unit_test {

	class TestProgramEndEventHandlerTest : public testing::Test
	{
		void SetUp()
		{
			auto testProgramJSONBuilder = buildTestProgramJSONBuilder();

			m_service = std::unique_ptr<service::TestProgramEndEventHandler>(new service::TestProgramEndEventHandler
							(m_testProgram, std::move(testProgramJSONBuilder)) );
		}

		std::unique_ptr<service::ITestProgramJSONBuilder> buildTestProgramJSONBuilder()
		{
			auto testProgramJSONBuilder = std::make_unique<MockTestProgramJSONBuilder>();
			m_testProgramJSONBuilder = testProgramJSONBuilder.get();
			return testProgramJSONBuilder;
		}

	protected:
		std::unique_ptr<service::TestProgramEndEventHandler> m_service;
		model::TestProgram m_testProgram;
		MockTestProgramJSONBuilder* m_testProgramJSONBuilder;
	};


	TEST_F(TestProgramEndEventHandlerTest, testHandleTestProgramEndBuildsTestProgramJSONs)
	{
		EXPECT_CALL(*m_testProgramJSONBuilder, buildJSONFiles(m_testProgram));
		m_service->handleTestProgramEnd();
	}

}}}
