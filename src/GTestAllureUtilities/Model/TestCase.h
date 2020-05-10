#pragma once

#include "Action.h"
#include "Label.h"
#include "Link.h"
#include "Stage.h"
#include "Status.h"

#include <string>


namespace systelab { namespace gtest_allure { namespace model {

	class TestCase
	{
	public:
		TestCase();
		TestCase(const TestCase&);
		virtual ~TestCase() = default;

		std::string getName() const;
		void setName(const std::string&);

		const std::vector<Action>& getActions() const;
		std::vector<Action>& getActions();
		void addAction(const Action&);

		virtual TestCase& operator= (const TestCase&);
		friend bool operator== (const TestCase& lhs, const TestCase& rhs);
		friend bool operator!= (const TestCase& lhs, const TestCase& rhs);

	private:
		std::string m_name;
		std::vector<Action> m_actions;
	};

}}}
