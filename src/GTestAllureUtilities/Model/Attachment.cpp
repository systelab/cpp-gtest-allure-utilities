#include "Attachment.h"


namespace systelab { namespace gtest_allure { namespace model {

	Attachment::Attachment()
		:m_name("")
		,m_source("")
		,m_type("")
	{
	}

	Attachment::Attachment(const Attachment& other)
		:m_name(other.m_name)
		,m_source(other.m_source)
		,m_type(other.m_type)
	{
	}

	std::string Attachment::getName() const
	{
		return m_name;
	}

	std::string Attachment::getSource() const
	{
		return m_source;
	}

	std::string Attachment::getType() const
	{
		return m_type;
	}

	void Attachment::setName(const std::string& name)
	{
		m_name = name;
	}

	void Attachment::setSource(const std::string& source)
	{
		m_source = source;
	}

	void Attachment::setType(const std::string& type)
	{
		m_type = type;
	}

	Attachment& Attachment::operator= (const Attachment& other)
	{
		m_name = other.m_name;
		m_source = other.m_source;
		m_type = other.m_type;
		return *this;
	}

	bool operator== (const Attachment& lhs, const Attachment& rhs)
	{
		return (lhs.m_name == rhs.m_name) &&
			   (lhs.m_source == rhs.m_source) &&
			   (lhs.m_type == rhs.m_type);
	}

	bool operator!= (const Attachment& lhs, const Attachment& rhs)
	{
		return !(lhs == rhs);
	}

}}}