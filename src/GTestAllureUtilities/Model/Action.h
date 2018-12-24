#pragma once

#include "ExpectedResult.h"

#include <string>
#include <vector>


namespace systelab { namespace gtest_allure_utilities { namespace model {

	enum class Stage;
	enum class Status;

	class Action
	{
	public:
		Action();
		Action(const Action&);
		virtual ~Action() = default;

		std::string getName() const;
		Status getStatus() const;
		Stage getStage() const;
		long getStart() const;
		long getStop() const;

		void setName(const std::string&);
		void setStatus(Status);
		void setStage(Stage);
		void setStart(long);
		void setStop(long);

		const std::vector<ExpectedResult>& getExpectedResults() const;
		void addExpectedResult(const ExpectedResult&);

		virtual Action& operator= (const Action&);
		friend bool operator== (const Action& lhs, const Action& rhs);
		friend bool operator!= (const Action& lhs, const Action& rhs);

	private:
		std::string m_name;
		Status m_status;
		Stage m_stage;
		long m_start;
		long m_stop;

		std::vector<ExpectedResult> m_expectedResults;
	};

}}}
