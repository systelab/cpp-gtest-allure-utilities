#pragma once

#include "ITestSuitePropertySetter.h"

#include <memory>


namespace systelab { namespace gtest_allure { namespace model {
	class TestProgram;
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class TestSuitePropertySetter : public ITestSuitePropertySetter
	{
	public:
		TestSuitePropertySetter(model::TestProgram&);
		virtual ~TestSuitePropertySetter();

		void setProperty(const std::string& name, const std::string& value) const override;

	private:
		model::TestSuite& getRunningTestSuite() const;

	private:
		model::TestProgram& m_testProgram;
	};

}}}
