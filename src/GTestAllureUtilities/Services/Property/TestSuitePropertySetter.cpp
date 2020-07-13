#include "TestSuitePropertySetter.h"

#include "Model/TestProgram.h"
#include "Model/TestProperty.h"

#include "Services/System/ITimeService.h"

#include <regex>


namespace systelab { namespace gtest_allure { namespace service {

	TestSuitePropertySetter::TestSuitePropertySetter(model::TestProgram& testProgram)
		:m_testProgram(testProgram)
	{
	}

	TestSuitePropertySetter::~TestSuitePropertySetter() = default;

	void TestSuitePropertySetter::setProperty(const std::string& name, const std::string& value) const
	{
		model::TestSuite& testSuite = getRunningTestSuite();
		if (name == model::test_property::TMS_ID_PROPERTY)
		{
			testSuite.setTmsId(value);
		}
		else if (name == model::test_property::NAME_PROPERTY)
		{
			testSuite.setName(value);
		}
		else
		{
			model::Label label;
			label.setName(name);
			label.setValue(value);
			testSuite.addLabel(label);
		}
	}

	model::TestSuite& TestSuitePropertySetter::getRunningTestSuite() const
	{
		unsigned int nTestSuites = (unsigned int) m_testProgram.getTestSuitesCount();
		for (unsigned int i = 0; i < nTestSuites; i++)
		{
			model::TestSuite& testSuite = m_testProgram.getTestSuite(i);
			if (testSuite.getStage() == model::Stage::RUNNING)
			{
				return testSuite;
			}
		}

		throw NoRunningTestSuiteException();
	}

}}}
