#include "Step.h"

#include "Stage.h"
#include "Status.h"


namespace systelab { namespace gtest_allure { namespace model {

	Step::Step()
		:m_name("")
		,m_status(Status::UNKNOWN)
		,m_stage(Stage::PENDING)
		,m_start(0)
		,m_stop(0)
	{
	}

	Step::Step(const Step& other)
		:m_name(other.m_name)
		,m_status(other.m_status)
		,m_stage(other.m_stage)
		,m_start(other.m_start)
		,m_stop(other.m_stop)
	{
	}

	std::string Step::getName() const
	{
		return m_name;
	}

	model::Status Step::getStatus() const
	{
		return m_status;
	}

	model::Stage Step::getStage() const
	{
		return m_stage;
	}

	time_t Step::getStart() const
	{
		return m_start;
	}

	time_t Step::getStop() const
	{
		return m_stop;
	}

	void Step::setName(const std::string& name)
	{
		m_name = name;
	}

	void Step::setStatus(Status status)
	{
		m_status = status;
	}

	void Step::setStage(Stage stage)
	{
		m_stage = stage;
	}

	void Step::setStart(time_t start)
	{
		m_start = start;
	}

	void Step::setStop(time_t stop)
	{
		m_stop = stop;
	}

	Step& Step::operator= (const Step& other)
	{
		m_name = other.m_name;
		m_status = other.m_status;
		m_stage = other.m_stage;
		m_start = other.m_start;
		m_stop = other.m_stop;

		return *this;
	}

	bool operator== (const Step& lhs, const Step& rhs)
	{
		return (lhs.m_name == rhs.m_name) &&
			   (lhs.m_status == rhs.m_status) &&
			   (lhs.m_stage == rhs.m_stage) &&
			   (lhs.m_start == rhs.m_start) &&
			   (lhs.m_stop == rhs.m_stop);
	}

	bool operator!= (const Step& lhs, const Step& rhs)
	{
		return !(lhs == rhs);
	}

}}}
