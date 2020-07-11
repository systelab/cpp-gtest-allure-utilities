#include "TestCase.h"


namespace systelab { namespace gtest_allure { namespace model {

	TestCase::TestCase()
		:m_name("")
		,m_status(Status::UNKNOWN)
		,m_stage(Stage::PENDING)
		,m_start(0)
		,m_stop(0)
		,m_steps()
	{
	}

	TestCase::TestCase(const TestCase& other)
		:m_name(other.m_name)
		,m_status(other.m_status)
		,m_stage(other.m_stage)
		,m_start(other.m_start)
		,m_stop(other.m_stop)
		,m_steps()
	{
		for (const auto& step : other.m_steps)
		{
			m_steps.push_back(std::unique_ptr<Step>(step->clone()));
		}
	}

	std::string TestCase::getName() const
	{
		return m_name;
	}

	Status TestCase::getStatus() const
	{
		return m_status;
	}

	Stage TestCase::getStage() const
	{
		return m_stage;
	}

	time_t TestCase::getStart() const
	{
		return m_start;
	}

	time_t TestCase::getStop() const
	{
		return m_stop;
	}

	void TestCase::setName(const std::string& name)
	{
		m_name = name;
	}

	void TestCase::setStatus(Status status)
	{
		m_status = status;
	}

	void TestCase::setStage(Stage stage)
	{
		m_stage = stage;
	}

	void TestCase::setStart(time_t start)
	{
		m_start = start;
	}

	void TestCase::setStop(time_t stop)
	{
		m_stop = stop;
	}

	unsigned int TestCase::getStepCount() const
	{
		return (unsigned int) m_steps.size();
	}

	const Step* TestCase::getStep(unsigned int index) const
	{
		return m_steps[index].get();
	}

	Step* TestCase::getStep(unsigned int index)
	{
		return m_steps[index].get();
	}

	void TestCase::addStep(std::unique_ptr<Step> step)
	{
		m_steps.push_back(std::move(step));
	}

	TestCase& TestCase::operator= (const TestCase& other)
	{
		m_name = other.m_name;
		m_status = other.m_status;
		m_stage = other.m_stage;
		m_start = other.m_start;
		m_stop = other.m_stop;

		m_steps = std::vector< std::unique_ptr<Step> >();
		for (const auto& step : other.m_steps)
		{
			m_steps.push_back(std::unique_ptr<Step>(step->clone()));
		}

		return *this;
	}

	bool operator== (const TestCase& lhs, const TestCase& rhs)
	{
		if ((lhs.m_name != rhs.m_name) &&
			(lhs.m_status != rhs.m_status) &&
			(lhs.m_stage != rhs.m_stage) &&
			(lhs.m_start != rhs.m_start) &&
			(lhs.m_stop != rhs.m_stop) &&
			(lhs.m_steps.size() != rhs.m_steps.size()))
		{
			return false;
		}

		unsigned int nSteps = (unsigned int) lhs.m_steps.size();
		for (unsigned int i = 0; i < nSteps; i++)
		{
			if ((*lhs.m_steps[i]) != (*rhs.m_steps[i]))
			{
				return false;
			}
		}

		return true;
	}

	bool operator!= (const TestCase& lhs, const TestCase& rhs)
	{
		return !(lhs == rhs);
	}

}}}
