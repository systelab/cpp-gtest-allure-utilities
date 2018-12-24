#pragma once

#include "TestCase.h"


namespace systelab { namespace gtest_allure_utilities { namespace model {

	class TestSuite
	{
	public:
		TestSuite();
		TestSuite(const TestSuite&);
		virtual ~TestSuite() = default;

		size_t getTestCasesCount() const;
		const TestCase& getTestCase(unsigned int index) const;
		void addTestCase(const TestCase&);

		virtual TestSuite& operator= (const TestSuite&);
		friend bool operator== (const TestSuite& lhs, const TestSuite& rhs);
		friend bool operator!= (const TestSuite& lhs, const TestSuite& rhs);

	private:
		std::vector<TestCase> m_testCases;
	};

}}}
