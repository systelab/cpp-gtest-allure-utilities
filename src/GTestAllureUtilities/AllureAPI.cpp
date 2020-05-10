#include "AllureAPI.h"

#include "Services/ServicesFactory.h"


namespace systelab { namespace gtest_allure {

	model::TestProgram AllureAPI::m_testProgram = model::TestProgram();

	model::TestProgram& AllureAPI::getTestProgram()
	{
		return m_testProgram;
	}

	void AllureAPI::setTestProgramName(const std::string& name)
	{
		m_testProgram.setName(name);
	}

	void AllureAPI::setOutputFolder(const std::string& outputFolder)
	{
		m_testProgram.setOutputFolder(outputFolder);
	}

	std::unique_ptr<::testing::TestEventListener> AllureAPI::buildListener()
	{
		service::ServicesFactory servicesFactory(m_testProgram);
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