#include "AllureAPI.h"

#include "Services/ServicesFactory.h"


namespace systelab { namespace gtest_allure_utilities {

	model::TestSuite AllureAPI::m_testSuite = model::TestSuite();

	model::TestSuite& AllureAPI::getTestSuite()
	{
		return m_testSuite;
	}

	void AllureAPI::setTestSuiteName(const std::string& name)
	{
		m_testSuite.setName(name);
	}

	void AllureAPI::setOutputFolder(const std::string& outputFolder)
	{
		m_testSuite.setOutputFolder(outputFolder);
	}

	std::unique_ptr<::testing::TestEventListener> AllureAPI::buildListener()
	{
		service::ServicesFactory servicesFactory(m_testSuite);
		return servicesFactory.buildGTestEventListener();
	}

	void AllureAPI::addAction(const std::string& name, std::function<void()> actionFunction)
	{
		// TODO
	}

	void AllureAPI::addExpectedResult(const std::string& name, std::function<void()> verificationFunction)
	{

	}

	void AllureAPI::addParameter(const std::string& name, const std::string& value)
	{

	}

}}