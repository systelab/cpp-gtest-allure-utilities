#pragma once

#include "Model/TestProgram.h"
#include "Model/Format.h"

#include <functional>
#include <gtest/gtest.h>
#include <memory>


namespace systelab { namespace gtest_allure {

	namespace service {
		class IServicesFactory;
	}

	class AllureAPI
	{
	public:
		static std::unique_ptr<::testing::TestEventListener> buildListener();

		static model::TestProgram& getTestProgram();
		static void setTestProgramName(const std::string&);
		static void setOutputFolder(const std::string&);
		static void setTMSLinksPattern(const std::string&);
		static void setFormat(model::Format format);

		static void setTMSId(const std::string&);
		static void setTestSuiteName(const std::string&);
		static void setTestSuiteDescription(const std::string&);
		static void setTestSuiteEpic(const std::string&);
		static void setTestSuiteSeverity(const std::string&);
		static void setTestSuiteLabel(const std::string& name, const std::string& value);

		static void setTestCaseName(const std::string&);
		static void addAction(const std::string& name, std::function<void()>);
		static void addExpectedResult(const std::string& name, std::function<void()>);

	private:
		static void addStep(const std::string& name, bool isAction, std::function<void()>);
		static service::IServicesFactory* getServicesFactory();

	private:
		static model::TestProgram m_testProgram;
		static service::IServicesFactory* m_servicesFactory;
	};

}}
