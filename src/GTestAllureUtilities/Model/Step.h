#pragma once

#include <string>
#include <vector>


namespace systelab { namespace gtest_allure { namespace model {

	enum class Stage;
	enum class Status;
	enum class StepType;

	class Step
	{
	public:
		Step();
		Step(const Step&);
		virtual ~Step() = default;

		virtual StepType getStepType() const = 0;
		virtual Step* clone() const = 0;

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

		virtual Step& operator= (const Step&);
		friend bool operator== (const Step& lhs, const Step& rhs);
		friend bool operator!= (const Step& lhs, const Step& rhs);

	private:
		std::string m_name;
		Status m_status;
		Stage m_stage;
		time_t m_start;
		time_t m_stop;
	};

}}}
