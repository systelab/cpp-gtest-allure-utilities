#include "TestSuite.h"


namespace systelab { namespace gtest_allure_utilities { namespace model {

	TestSuite::TestSuite()
		:m_name()
		,m_outputFolder()
		,m_testCases()
	{
	}

	TestSuite::TestSuite(const TestSuite& other)
		:m_name(other.m_name)
		,m_outputFolder(other.m_outputFolder)
		,m_testCases(other.m_testCases)
	{
	}

	std::string TestSuite::getName() const
	{
		return m_name;
	}

	std::string TestSuite::getOutputFolder() const
	{
		return m_outputFolder;
	}

	void TestSuite::setName(const std::string& name)
	{
		m_name = name;
	}

	void TestSuite::setOutputFolder(const std::string& outputFolder)
	{
		m_outputFolder = outputFolder;
	}

	size_t TestSuite::getTestCasesCount() const
	{
		return m_testCases.size();
	}

	const TestCase& TestSuite::getTestCase(unsigned int index) const
	{
		return m_testCases[index];
	}

	void TestSuite::addTestCase(const TestCase& testCase)
	{
		m_testCases.push_back(testCase);
	}

	TestSuite& TestSuite::operator= (const TestSuite& other)
	{
		m_name = other.m_name;
		m_outputFolder = other.m_outputFolder;
		m_testCases = other.m_testCases;
		return *this;
	}

	bool operator== (const TestSuite& lhs, const TestSuite& rhs)
	{
		return (lhs.m_testCases == rhs.m_testCases);
	}

	bool operator!= (const TestSuite& lhs, const TestSuite& rhs)
	{
		return !(lhs == rhs);
	}

}}}