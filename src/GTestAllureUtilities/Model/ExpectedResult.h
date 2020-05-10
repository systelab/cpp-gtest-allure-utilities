#pragma once

#include "Step.h"


namespace systelab { namespace gtest_allure { namespace model {

	class ExpectedResult : public Step
	{
	public:
		ExpectedResult();
		ExpectedResult(const ExpectedResult&);
		virtual ~ExpectedResult() = default;

		StepType getStepType() const override;
		Step* clone() const override;
	};

}}}
