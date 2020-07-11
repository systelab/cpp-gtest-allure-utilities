#pragma once

#include "Stage.h"
#include "Status.h"
#include "Step.h"

#include <memory>
#include <string>
#include <vector>


namespace systelab { namespace gtest_allure { namespace model {

	class TestCase
	{
	public:
		TestCase();
		TestCase(const TestCase&);
		virtual ~TestCase() = default;

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

		unsigned int getStepCount() const;
		const Step* getStep(unsigned int index) const;
		Step* getStep(unsigned int index);
		void addStep(std::unique_ptr<Step>);

		virtual TestCase& operator= (const TestCase&);
		friend bool operator== (const TestCase& lhs, const TestCase& rhs);
		friend bool operator!= (const TestCase& lhs, const TestCase& rhs);

	private:
		std::string m_name;
		Status m_status;
		Stage m_stage;
		time_t m_start;
		time_t m_stop;

		std::vector< std::unique_ptr<Step> > m_steps;
	};

}}}
