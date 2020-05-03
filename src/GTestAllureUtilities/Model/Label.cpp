#include "Label.h"


namespace systelab { namespace gtest_allure { namespace model {

	Label::Label()
		:m_name("")
		,m_value("")
	{
	}

	Label::Label(const Label& other)
		:m_name(other.m_name)
		,m_value(other.m_value)
	{
	}

	std::string Label::getName() const
	{
		return m_name;
	}

	std::string Label::getValue() const
	{
		return m_value;
	}

	void Label::setName(const std::string& name)
	{
		m_name = name;
	}

	void Label::setValue(const std::string& value)
	{
		m_value = value;
	}

	Label& Label::operator= (const Label& other)
	{
		m_name = other.m_name;
		m_value = other.m_value;
		return *this;
	}

	bool operator== (const Label& lhs, const Label& rhs)
	{
		return (lhs.m_name == rhs.m_name) &&
			   (lhs.m_value == rhs.m_value);
	}

	bool operator!= (const Label& lhs, const Label& rhs)
	{
		return !(lhs == rhs);
	}

}}}