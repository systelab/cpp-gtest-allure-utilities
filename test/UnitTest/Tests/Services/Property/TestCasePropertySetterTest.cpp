#include "stdafx.h"
#include "GTestAllureUtilities/Services/Property/TestCasePropertySetter.h"

#include "GTestAllureUtilities/Model/TestProgram.h"
#include "GTestAllureUtilities/Model/TestProperty.h"


using namespace testing;
using namespace systelab::gtest_allure;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class TestCasePropertySetterTest : public testing::Test
	{
	public:
		void SetUp()
		{
			setUpTestProgram();
			m_service = std::make_unique<service::TestCasePropertySetter>(m_testProgram);
		}

		void setUpTestProgram()
		{
			model::TestSuite finishedTestSuite;
			finishedTestSuite.setStage(model::Stage::FINISHED);
			finishedTestSuite.addTestCase(buildTestCase("TC-1.1", model::Stage::FINISHED));
			finishedTestSuite.addTestCase(buildTestCase("TC-1.2", model::Stage::FINISHED));
			m_testProgram.addTestSuite(finishedTestSuite);

			model::TestSuite runningTestSuite;
			runningTestSuite.setStage(model::Stage::RUNNING);
			runningTestSuite.addTestCase(buildTestCase("TC-2.1", model::Stage::FINISHED));
			runningTestSuite.addTestCase(buildTestCase("TC-2.2", model::Stage::RUNNING));
			m_testProgram.addTestSuite(runningTestSuite);

			m_runningTestCase = &m_testProgram.getTestSuite(1).getTestCases()[1];
		}

		model::TestCase buildTestCase(const std::string& name, model::Stage stage)
		{
			model::TestCase testCase;
			testCase.setName(name);
			testCase.setStage(stage);
			testCase.setStatus(model::Status::UNKNOWN);

			return testCase;
		}

	protected:
		std::unique_ptr<service::TestCasePropertySetter> m_service;
		model::TestProgram m_testProgram;
		model::TestCase* m_runningTestCase;
	};


	TEST_F(TestCasePropertySetterTest, testSetPropertyForNameUpdatesNameOfRunningTestSuite)
	{
		std::string newTestCaseName = "NewTestCaseName";
		m_service->setProperty(model::test_property::NAME_PROPERTY, newTestCaseName);
		ASSERT_EQ(newTestCaseName, m_runningTestCase->getName());
	}

	TEST_F(TestCasePropertySetterTest, testSetPropertyForCustomPropertyThrowsInvalidPropertyException)
	{
		ASSERT_THROW(m_service->setProperty("CustomProperty", "CustomValue"),
					 service::ITestCasePropertySetter::InvalidPropertyException);
	}

	TEST_F(TestCasePropertySetterTest, testSetPropertyThrowsExceptionWhenNoRunningTestSuite)
	{
		m_testProgram.getTestSuite(1).setStage(model::Stage::FINISHED);
		ASSERT_THROW(m_service->setProperty(model::test_property::NAME_PROPERTY, "NewTestCaseName"),
			service::ITestCasePropertySetter::NoRunningTestSuiteException);
	}

	TEST_F(TestCasePropertySetterTest, testSetPropertyThrowsExceptionWhenNoRunningTestCase)
	{
		m_runningTestCase->setStage(model::Stage::FINISHED);
		ASSERT_THROW(m_service->setProperty(model::test_property::NAME_PROPERTY, "NewTestCaseName"),
					 service::ITestCasePropertySetter::NoRunningTestCaseException);
	}

}}}
