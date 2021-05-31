#include "TestProgram.h"


namespace systelab { namespace gtest_allure { namespace model {

	TestProgram::TestProgram()
		:m_name()
		,m_outputFolder(".")
		,m_tmsLinksPattern("http://{}")
		,m_testSuites()
		,m_format(Format::DEFAULT)
	{
	}

	TestProgram::TestProgram(const TestProgram& other)
		:m_name(other.m_name)
		,m_outputFolder(other.m_outputFolder)
		,m_tmsLinksPattern(other.m_tmsLinksPattern)
		,m_testSuites(other.m_testSuites)
		,m_format(other.m_format)
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

	std::string TestProgram::getTMSLinksPattern() const
	{
		return m_tmsLinksPattern;
	}

	Format TestProgram::getFormat() const
	{
		return m_format;
	}

	void TestProgram::setName(const std::string& name)
	{
		m_name = name;
	}

	void TestProgram::setOutputFolder(const std::string& outputFolder)
	{
		m_outputFolder = outputFolder;
	}

	void TestProgram::setTMSLinksPattern(const std::string& tmsLinksPattern)
	{
		m_tmsLinksPattern = tmsLinksPattern;
	}

	void TestProgram::setFormat(Format format)
	{
		m_format = format;
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
		m_tmsLinksPattern = other.m_tmsLinksPattern;
		m_testSuites = other.m_testSuites;
		return *this;
	}

	bool operator== (const TestProgram& lhs, const TestProgram& rhs)
	{
		return (lhs.m_name == rhs.m_name) &&
			   (lhs.m_outputFolder == rhs.m_outputFolder) &&
			   (lhs.m_tmsLinksPattern == rhs.m_tmsLinksPattern) &&
			   (lhs.m_testSuites == rhs.m_testSuites);
	}

	bool operator!= (const TestProgram& lhs, const TestProgram& rhs)
	{
		return !(lhs == rhs);
	}

}}}