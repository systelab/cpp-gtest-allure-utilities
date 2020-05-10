#pragma once

#include "TestSuite.h"


namespace systelab { namespace gtest_allure { namespace model {

	class TestProgram
	{
	public:
		TestProgram();
		TestProgram(const TestProgram&);
		virtual ~TestProgram() = default;

		std::string getName() const;
		std::string getOutputFolder() const;
		void setName(const std::string&);
		void setOutputFolder(const std::string&);

		size_t getTestSuitesCount() const;
		const TestSuite& getTestSuite(unsigned int index) const;
		TestSuite& getTestSuite(unsigned int index);
		void addTestSuite(const TestSuite&);
		void clearTestSuites();

		virtual TestProgram& operator= (const TestProgram&);
		friend bool operator== (const TestProgram& lhs, const TestProgram& rhs);
		friend bool operator!= (const TestProgram& lhs, const TestProgram& rhs);

	private:
		std::string m_name;
		std::string m_outputFolder;
		std::vector<TestSuite> m_testSuites;
	};

}}}
