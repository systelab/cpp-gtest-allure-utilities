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
		long getStart() const;
		long getStop() const;

		void setName(const std::string&);
		void setStatus(Status);
		void setStage(Stage);
		void setStart(long);
		void setStop(long);

		const std::vector<Parameter>& getParameters() const;
		void addParameter(const Parameter&);

		virtual ExpectedResult& operator= (const ExpectedResult&);
		friend bool operator== (const ExpectedResult& lhs, const ExpectedResult& rhs);
		friend bool operator!= (const ExpectedResult& lhs, const ExpectedResult& rhs);

	private:
		std::string m_name;
		Status m_status;
		Stage m_stage;
		long m_start;
		long m_stop;

		std::vector<Parameter> m_parameters;
	};

}}}
