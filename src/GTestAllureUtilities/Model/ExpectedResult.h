#pragma once

#include "Parameter.h"

#include <string>
#include <vector>


namespace systelab { namespace gtest_allure_utilities { namespace model {

	enum class Stage;
	enum class Status;

	class ExpectedResult
	{
	public:
		ExpectedResult();
		ExpectedResult(const ExpectedResult&);
		virtual ~ExpectedResult() = default;

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

		const std::vector<Parameter>& getParameters() const;
		void addParameter(const Parameter&);

		virtual ExpectedResult& operator= (const ExpectedResult&);
		friend bool operator== (const ExpectedResult& lhs, const ExpectedResult& rhs);
		friend bool operator!= (const ExpectedResult& lhs, const ExpectedResult& rhs);

	private:
		std::string m_name;
		Status m_status;
		Stage m_stage;
		time_t m_start;
		time_t m_stop;

		std::vector<Parameter> m_parameters;
	};

}}}
