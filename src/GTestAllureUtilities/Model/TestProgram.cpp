#include "TestProgram.h"


namespace systelab { namespace gtest_allure { namespace model {

	TestProgram::TestProgram()
		:m_name()
		,m_outputFolder(".")
		,m_testSuites()
	{
	}

	TestProgram::TestProgram(const TestProgram& other)
		:m_name(other.m_name)
		,m_outputFolder(other.m_outputFolder)
		,m_testSuites(other.m_testSuites)
	{
	}

	std::string TestProgram::getName() const
	{
		return m_name;
	}

	std::string TestProgram::getOutputFolder() const
	{
		return m_outputFolder;
	}

	void TestProgram::setName(const std::string& name)
	{
		m_name = name;
	}

	void TestProgram::setOutputFolder(const std::string& outputFolder)
	{
		m_outputFolder = outputFolder;
	}

	size_t TestProgram::getTestSuitesCount() const
	{
		return m_testSuites.size();
	}

	const TestSuite& TestProgram::getTestSuite(unsigned int index) const
	{
		return m_testSuites[index];
	}

	TestSuite& TestProgram::getTestSuite(unsigned int index)
	{
		return m_testSuites[index];
	}

	void TestProgram::addTestSuite(const TestSuite& testSuite)
	{
		m_testSuites.push_back(testSuite);
	}

	void TestProgram::clearTestSuites()
	{
		m_testSuites.clear();
	}

	TestProgram& TestProgram::operator= (const TestProgram& other)
	{
		m_name = other.m_name;
		m_outputFolder = other.m_outputFolder;
		m_testSuites = other.m_testSuites;
		return *this;
	}

	bool operator== (const TestProgram& lhs, const TestProgram& rhs)
	{
		return (lhs.m_testSuites == rhs.m_testSuites);
	}

	bool operator!= (const TestProgram& lhs, const TestProgram& rhs)
	{
		return !(lhs == rhs);
	}

}}}