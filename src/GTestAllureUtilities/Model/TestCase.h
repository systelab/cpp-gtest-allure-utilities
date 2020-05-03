#pragma once

#include "Action.h"
#include "Label.h"
#include "Link.h"
#include "Stage.h"
#include "Status.h"

#include <string>


namespace systelab { namespace gtest_allure { namespace model {

	class TestCase
	{
	public:
		TestCase();
		TestCase(const TestCase&);
		virtual ~TestCase() = default;

		std::string getUUID() const;
		std::string getHistoryId() const;
		std::string getName() const;
		std::string getDescription() const;
		Status getStatus() const;
		Stage getStage() const;
		time_t getStart() const;
		time_t getStop() const;

		void setUUID(const std::string&);
		void setHistoryId(const std::string&);
		void setName(const std::string&);
		void setDescription(const std::string&);
		void setStatus(Status);
		void setStage(Stage);
		void setStart(time_t);
		void setStop(time_t);

		const std::vector<Label>& getLabels() const;
		void addLabel(const Label&);

		const std::vector<Link>& getLinks() const;
		void addLink(const Link&);

		const std::vector<Action>& getActions() const;
		void addAction(const Action&);

		virtual TestCase& operator= (const TestCase&);
		friend bool operator== (const TestCase& lhs, const TestCase& rhs);
		friend bool operator!= (const TestCase& lhs, const TestCase& rhs);

	private:
		std::string m_uuid;
		std::string m_historyId;
		std::string m_name;
		std::string m_description;
		Status m_status;
		Stage m_stage;
		time_t m_start;
		time_t m_stop;

		std::vector<Label> m_labels;
		std::vector<Link> m_links;
		std::vector<Action> m_actions;
	};

}}}
