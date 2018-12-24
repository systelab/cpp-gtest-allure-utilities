#include "Parameter.h"


namespace systelab { namespace gtest_allure_utilities { namespace model {

	Parameter::Parameter()
		:m_name("")
		,m_value("")
	{
	}

	Parameter::Parameter(const Parameter& other)
		:m_name(other.m_name)
		,m_value(other.m_value)
	{
	}

	std::string Parameter::getName() const
	{
		return m_name;
	}

	std::string Parameter::getValue() const
	{
		return m_value;
	}

	void Parameter::setName(const std::string& name)
	{
		m_name = name;
	}

	void Parameter::setValue(const std::string& value)
	{
		m_value = value;
	}

	Parameter& Parameter::operator= (const Parameter& other)
	{
		m_name = other.m_name;
		m_value = other.m_value;
		return *this;
	}

	bool operator== (const Parameter& lhs, const Parameter& rhs)
	{
		return (lhs.m_name == rhs.m_name) &&
			   (lhs.m_value == rhs.m_value);
	}

	bool operator!= (const Parameter& lhs, const Parameter& rhs)
	{
		return !(lhs == rhs);
	}

}}}