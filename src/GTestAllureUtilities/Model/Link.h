#pragma once

#include <string>


namespace systelab { namespace gtest_allure_utilities { namespace model {

	class Link
	{
	public:
		Link();
		Link(const Link&);
		virtual ~Link() = default;

		std::string getName() const;
		std::string getURL() const;
		std::string getType() const;

		void setName(const std::string&);
		void setURL(const std::string&);
		void setType(const std::string&);

		virtual Link& operator= (const Link&);
		friend bool operator== (const Link& lhs, const Link& rhs);
		friend bool operator!= (const Link& lhs, const Link& rhs);

	private:
		std::string m_name;
		std::string m_url;
		std::string m_type;
	};

}}}
