#include "TestSuite.h"


namespace systelab { namespace gtest_allure_utilities { namespace model {

	TestSuite::TestSuite()
		:m_testCases()
	{
	}

	TestSuite::TestSuite(const TestSuite& other)
		:m_testCases(other.m_testCases)
	{
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