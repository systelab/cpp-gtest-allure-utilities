#include "TestCasePropertySetter.h"

#include "Model/TestProgram.h"
#include "Model/TestProperty.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestCasePropertySetter::TestCasePropertySetter(model::TestProgram& testProgram)
		:m_testProgram(testProgram)
	{
	}

	TestCasePropertySetter::~TestCasePropertySetter() = default;

	void TestCasePropertySetter::setProperty(const std::string& name, const std::string& value) const
	{
		model::TestCase& testCase = getRunningTestCase();
		if (name == model::test_property::NAME_PROPERTY)
		{
			testCase.setName(value);
		}
		else
		{
			throw InvalidPropertyException(name);
		}
	}

	model::TestCase& TestCasePropertySetter::getRunningTestCase() const
	{
		auto& testSuite = getRunningTestSuite();
		for (model::TestCase& testCase : testSuite.getTestCases())
		{
			if (testCase.getStage() == model::Stage::RUNNING)
			{
				return testCase;
			}
		}

		throw NoRunningTestCaseException();
	}

	model::TestSuite& TestCasePropertySetter::getRunningTestSuite() const
	{
		unsigned int nTestSuites = (unsigned int)m_testProgram.getTestSuitesCount();
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
