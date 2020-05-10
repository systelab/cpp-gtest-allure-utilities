#include "TestCase.h"


namespace systelab { namespace gtest_allure { namespace model {

	TestCase::TestCase()
		:m_name("")
		,m_actions()
	{
	}

	TestCase::TestCase(const TestCase& other)
		:m_name(other.m_name)
		,m_actions(other.m_actions)
	{
	}

	std::string TestCase::getName() const
	{
		return m_name;
	}

	void TestCase::setName(const std::string& name)
	{
		m_name = name;
	}

	const std::vector<Action>& TestCase::getActions() const
	{
		return m_actions;
	}

	std::vector<Action>& TestCase::getActions()
	{
		return m_actions;
	}

	void TestCase::addAction(const Action& action)
	{
		m_actions.push_back(action);
	}

	TestCase& TestCase::operator= (const TestCase& other)
	{
		m_name = other.m_name;
		m_actions = other.m_actions;

		return *this;
	}

	bool operator== (const TestCase& lhs, const TestCase& rhs)
	{
		return (lhs.m_name == rhs.m_name) &&
			   (lhs.m_actions == rhs.m_actions);
	}

	bool operator!= (const TestCase& lhs, const TestCase& rhs)
	{
		return !(lhs == rhs);
	}

}}}