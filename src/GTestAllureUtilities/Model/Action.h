#pragma once

#include "Step.h"


namespace systelab { namespace gtest_allure { namespace model {

	class Action : public Step
	{
	public:
		Action();
		Action(const Action&);
		virtual ~Action() = default;

		StepType getStepType() const override;
		Step* clone() const override;

	};

}}}
