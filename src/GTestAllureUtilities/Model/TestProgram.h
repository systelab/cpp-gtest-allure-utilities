#pragma once

#include "Format.h"
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
		std::string getTMSLinksPattern() const;
		Format getFormat() const;

		void setName(const std::string&);
		void setOutputFolder(const std::string&);
		void setTMSLinksPattern(const std::string&);
		void setFormat(Format);

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
		std::string m_tmsLinksPattern;
		std::vector<TestSuite> m_testSuites;
		Format m_format;
	};

}}}
