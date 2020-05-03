#pragma once

#include <string>


namespace systelab { namespace gtest_allure { namespace model {

	class Parameter
	{
	public:
		Parameter();
		Parameter(const Parameter&);
		virtual ~Parameter() = default;

		std::string getName() const;
		std::string getValue() const;

		void setName(const std::string&);
		void setValue(const std::string&);

		virtual Parameter& operator= (const Parameter&);
		friend bool operator== (const Parameter& lhs, const Parameter& rhs);
		friend bool operator!= (const Parameter& lhs, const Parameter& rhs);

	private:
		std::string m_name;
		std::string m_value;
	};

}}}
