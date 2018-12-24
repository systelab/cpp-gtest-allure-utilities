#include "Action.h"

#include "Stage.h"
#include "Status.h"


namespace systelab { namespace gtest_allure_utilities { namespace model {

	Action::Action()
		:m_name("")
		,m_status(Status::UNKNOWN)
		,m_stage(Stage::PENDING)
		,m_start(0)
		,m_stop(0)
		,m_expectedResults()
	{
	}

	Action::Action(const Action& other)
		:m_name(other.m_name)
		,m_status(other.m_status)
		,m_stage(other.m_stage)
		,m_start(other.m_start)
		,m_stop(other.m_stop)
		,m_expectedResults(other.m_expectedResults)
	{
	}

	std::string Action::getName() const
	{
		return m_name;
	}

	model::Status Action::getStatus() const
	{
		return m_status;
	}

	model::Stage Action::getStage() const
	{
		return m_stage;
	}

	long Action::getStart() const
	{
		return m_start;
	}

	long Action::getStop() const
	{
		return m_stop;
	}

	void Action::setName(const std::string& name)
	{
		m_name = name;
	}

	void Action::setStatus(Status status)
	{
		m_status = status;
	}

	void Action::setStage(Stage stage)
	{
		m_stage = stage;
	}

	void Action::setStart(long start)
	{
		m_start = start;
	}

	void Action::setStop(long stop)
	{
		m_stop = stop;
	}

	const std::vector<ExpectedResult>& Action::getExpectedResults() const
	{
		return m_expectedResults;
	}
	
	void Action::addExpectedResult(const ExpectedResult& expectedResult)
	{
		m_expectedResults.push_back(expectedResult);
	}

	Action& Action::operator= (const Action& other)
	{
		m_name = other.m_name;
		m_status = other.m_status;
		m_stage = other.m_stage;
		m_start = other.m_start;
		m_stop = other.m_stop;
		m_expectedResults = other.m_expectedResults;

		return *this;
	}

	bool operator== (const Action& lhs, const Action& rhs)
	{
		return (lhs.m_name == rhs.m_name) &&
			   (lhs.m_status == rhs.m_status) &&
			   (lhs.m_stage == rhs.m_stage) &&
			   (lhs.m_start == rhs.m_start) &&
			   (lhs.m_stop == rhs.m_stop) &&
			   (lhs.m_expectedResults == rhs.m_expectedResults);
	}

	bool operator!= (const Action& lhs, const Action& rhs)
	{
		return !(lhs == rhs);
	}

}}}
