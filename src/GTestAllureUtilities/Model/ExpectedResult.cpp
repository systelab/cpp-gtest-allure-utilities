#include "ExpectedResult.h"

#include "Stage.h"
#include "Status.h"


namespace systelab { namespace gtest_allure_utilities { namespace model {

	ExpectedResult::ExpectedResult()
		:m_name("")
		,m_status(Status::UNKNOWN)
		,m_stage(Stage::PENDING)
		,m_start(0)
		,m_stop(0)
		,m_parameters()
	{
	}

	ExpectedResult::ExpectedResult(const ExpectedResult& other)
		:m_name(other.m_name)
		,m_status(other.m_status)
		,m_stage(other.m_stage)
		,m_start(other.m_start)
		,m_stop(other.m_stop)
		,m_parameters(other.m_parameters)
	{
	}

	std::string ExpectedResult::getName() const
	{
		return m_name;
	}

	model::Status ExpectedResult::getStatus() const
	{
		return m_status;
	}

	model::Stage ExpectedResult::getStage() const
	{
		return m_stage;
	}

	time_t ExpectedResult::getStart() const
	{
		return m_start;
	}

	time_t ExpectedResult::getStop() const
	{
		return m_stop;
	}

	void ExpectedResult::setName(const std::string& name)
	{
		m_name = name;
	}

	void ExpectedResult::setStatus(Status status)
	{
		m_status = status;
	}

	void ExpectedResult::setStage(Stage stage)
	{
		m_stage = stage;
	}

	void ExpectedResult::setStart(time_t start)
	{
		m_start = start;
	}

	void ExpectedResult::setStop(time_t stop)
	{
		m_stop = stop;
	}

	const std::vector<Parameter>& ExpectedResult::getParameters() const
	{
		return m_parameters;
	}
	
	void ExpectedResult::addParameter(const Parameter& parameter)
	{
		m_parameters.push_back(parameter);
	}

	ExpectedResult& ExpectedResult::operator= (const ExpectedResult& other)
	{
		m_name = other.m_name;
		m_status = other.m_status;
		m_stage = other.m_stage;
		m_start = other.m_start;
		m_stop = other.m_stop;
		m_parameters = other.m_parameters;

		return *this;
	}

	bool operator== (const ExpectedResult& lhs, const ExpectedResult& rhs)
	{
		return (lhs.m_name == rhs.m_name) &&
			   (lhs.m_status == rhs.m_status) &&
			   (lhs.m_stage == rhs.m_stage) &&
			   (lhs.m_start == rhs.m_start) &&
			   (lhs.m_stop == rhs.m_stop) &&
			   (lhs.m_parameters == rhs.m_parameters);
	}

	bool operator!= (const ExpectedResult& lhs, const ExpectedResult& rhs)
	{
		return !(lhs == rhs);
	}

}}}
