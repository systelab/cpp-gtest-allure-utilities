#pragma once

#include "Model/TestSuite.h"

#include <functional>
#include <gtest/gtest.h>
#include <memory>


namespace systelab { namespace gtest_allure_utilities {

	class AllureAPI
	{
	public:
		static std::unique_ptr<::testing::TestEventListener> buildListener();

		static void setTestSuiteName(const std::string&);
		static void setOutputFolder(const std::string&);

		static void addAction(const std::string& name, std::function<void()>);
		static void addExpectedResult(const std::string& name, std::function<void()>);
		static void addParameter(const std::string& name, const std::string& value);

	private:
		static model::TestSuite m_testSuite;
	};

}}
