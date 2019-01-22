#pragma once

#include "TestCase.h"


namespace systelab { namespace gtest_allure_utilities { namespace model {

	class TestSuite
	{
	public:
		TestSuite();
		TestSuite(const TestSuite&);
		virtual ~TestSuite() = default;

		std::string getName() const;
		std::string getOutputFolder() const;
		void setName(const std::string&);
		void setOutputFolder(const std::string&);

		size_t getTestCasesCount() const;
		const TestCase& getTestCase(unsigned int index) const;
		TestCase& getTestCase(unsigned int index);
		void addTestCase(const TestCase&);
		void clearTestCases();

		virtual TestSuite& operator= (const TestSuite&);
		friend bool operator== (const TestSuite& lhs, const TestSuite& rhs);
		friend bool operator!= (const TestSuite& lhs, const TestSuite& rhs);

	private:
		std::string m_name;
		std::string m_outputFolder;
		std::vector<TestCase> m_testCases;
	};

}}}
