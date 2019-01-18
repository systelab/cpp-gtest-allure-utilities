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
		time_t getStart() const;
		time_t getStop() const;

		void setName(const std::string&);
		void setStatus(Status);
		void setStage(Stage);
		void setStart(time_t);
		void setStop(time_t);

		const std::vector<ExpectedResult>& getExpectedResults() const;
		void addExpectedResult(const ExpectedResult&);

		virtual Action& operator= (const Action&);
		friend bool operator== (const Action& lhs, const Action& rhs);
		friend bool operator!= (const Action& lhs, const Action& rhs);

	private:
		std::string m_name;
		Status m_status;
		Stage m_stage;
		time_t m_start;
		time_t m_stop;

		std::vector<ExpectedResult> m_expectedResults;
	};

}}}
