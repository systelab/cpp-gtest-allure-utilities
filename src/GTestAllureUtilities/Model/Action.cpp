#include "Action.h"

#include "StepType.h"


namespace systelab { namespace gtest_allure { namespace model {

	Action::Action()
		:Step()
	{
	}

	Action::Action(const Action& other)
		:Step(other)
	{
	}

	StepType Action::getStepType() const
	{
		return StepType::ACTION_STEP;
	}

	Step* Action::clone() const
	{
		return new Action(*this);
	}

}}}
