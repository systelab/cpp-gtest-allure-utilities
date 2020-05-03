#pragma once

#include <string>


namespace systelab { namespace gtest_allure { namespace model {

	class Attachment
	{
	public:
		Attachment();
		Attachment(const Attachment&);
		virtual ~Attachment() = default;

		std::string getName() const;
		std::string getSource() const;
		std::string getType() const;

		void setName(const std::string&);
		void setSource(const std::string&);
		void setType(const std::string&);

		virtual Attachment& operator= (const Attachment&);
		friend bool operator== (const Attachment& lhs, const Attachment& rhs);
		friend bool operator!= (const Attachment& lhs, const Attachment& rhs);

	private:
		std::string m_name;
		std::string m_source;
		std::string m_type;
	};

}}}
