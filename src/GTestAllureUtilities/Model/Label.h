#pragma once

#include <string>


namespace systelab { namespace gtest_allure_utilities { namespace model {

	class Label
	{
	public:
		Label();
		Label(const Label&);
		virtual ~Label() = default;

		std::string getName() const;
		std::string getValue() const;

		void setName(const std::string&);
		void setValue(const std::string&);

		virtual Label& operator= (const Label&);
		friend bool operator== (const Label& lhs, const Label& rhs);
		friend bool operator!= (const Label& lhs, const Label& rhs);

	private:
		std::string m_name;
		std::string m_value;
	};

}}}
