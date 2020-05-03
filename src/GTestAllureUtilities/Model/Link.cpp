#include "Link.h"


namespace systelab { namespace gtest_allure { namespace model {

	Link::Link()
		:m_name("")
		,m_url("")
		,m_type("")
	{
	}

	Link::Link(const Link& other)
		:m_name(other.m_name)
		,m_url(other.m_url)
		,m_type(other.m_type)
	{
	}

	std::string Link::getName() const
	{
		return m_name;
	}

	std::string Link::getURL() const
	{
		return m_url;
	}

	std::string Link::getType() const
	{
		return m_type;
	}

	void Link::setName(const std::string& name)
	{
		m_name = name;
	}

	void Link::setURL(const std::string& url)
	{
		m_url = url;
	}

	void Link::setType(const std::string& type)
	{
		m_type = type;
	}

	Link& Link::operator= (const Link& other)
	{
		m_name = other.m_name;
		m_url = other.m_url;
		m_type = other.m_type;
		return *this;
	}

	bool operator== (const Link& lhs, const Link& rhs)
	{
		return (lhs.m_name == rhs.m_name) &&
			   (lhs.m_url == rhs.m_url) &&
			   (lhs.m_type == rhs.m_type);
	}

	bool operator!= (const Link& lhs, const Link& rhs)
	{
		return !(lhs == rhs);
	}

}}}