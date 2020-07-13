#include "stdafx.h"
#include "GTestAllureUtilities/Services/Property/TestSuitePropertySetter.h"

#include "GTestAllureUtilities/Model/TestProgram.h"
#include "GTestAllureUtilities/Model/TestProperty.h"


using namespace testing;
using namespace systelab::gtest_allure;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class TestSuitePropertySetterTest : public testing::Test
	{
	public:
		void SetUp()
		{
			setUpTestProgram();
			m_service = std::make_unique<service::TestSuitePropertySetter>(m_testProgram);
		}

		void setUpTestProgram()
		{
			model::TestSuite finishedTestSuite;
			finishedTestSuite.setStage(model::Stage::FINISHED);
			m_testProgram.addTestSuite(finishedTestSuite);

			model::TestSuite runningTestSuite;
			runningTestSuite.setStage(model::Stage::RUNNING);
			m_testProgram.addTestSuite(runningTestSuite);

			m_runningTestSuite = &m_testProgram.getTestSuite(1);
		}

	protected:
		std::unique_ptr<service::TestSuitePropertySetter> m_service;
		model::TestProgram m_testProgram;
		model::TestSuite* m_runningTestSuite;
	};


	TEST_F(TestSuitePropertySetterTest, testSetPropertyForTMSIdUpdatesTMSIdOfRunningTestSuite)
	{
		std::string newTMSId = "NewTMSIdValue";
		m_service->setProperty(model::test_property::TMS_ID_PROPERTY, newTMSId);
		ASSERT_EQ(newTMSId, m_runningTestSuite->getTmsId());
	}

	TEST_F(TestSuitePropertySetterTest, testSetPropertyForNameUpdatesNameOfRunningTestSuite)
	{
		std::string newTestSuiteName = "NewTestSuiteName";
		m_service->setProperty(model::test_property::NAME_PROPERTY, newTestSuiteName);
		ASSERT_EQ(newTestSuiteName, m_runningTestSuite->getName());
	}

	TEST_F(TestSuitePropertySetterTest, testSetPropertyForCustomPropertyNameAddsLabelToTestSuite)
	{
		std::string customPropertyName = "CustomProperty";
		std::string customPropertyValue = "CustomValue";
		m_service->setProperty(customPropertyName, customPropertyValue);

		auto testSuiteLabels = m_runningTestSuite->getLabels();
		ASSERT_EQ(1, testSuiteLabels.size());
		ASSERT_EQ(customPropertyName, testSuiteLabels[0].getName());
		ASSERT_EQ(customPropertyValue, testSuiteLabels[0].getValue());
	}

	TEST_F(TestSuitePropertySetterTest, testSetPropertyThrowsExceptionWhenNoRunningTestSuite)
	{
		m_runningTestSuite->setStage(model::Stage::FINISHED);
		ASSERT_THROW(m_service->setProperty("PropertyName", "PropertyValue"),
					 service::ITestSuitePropertySetter::NoRunningTestSuiteException);
	}

}}}
