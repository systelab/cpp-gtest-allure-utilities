#pragma once

#include "Label.h"
#include "Link.h"
#include "Stage.h"
#include "Status.h"
#include "TestCase.h"


namespace systelab { namespace gtest_allure { namespace model {

	class TestSuite
	{
	public:
		TestSuite();
		TestSuite(const TestSuite&);
		virtual ~TestSuite() = default;

		std::string getUUID() const;
		std::string getName() const;
		std::string getTmsId() const;
		Status getStatus() const;
		Stage getStage() const;
		time_t getStart() const;
		time_t getStop() const;

		void setUUID(const std::string&);
		void setName(const std::string&);
		void setTmsId(const std::string&);
		void setStatus(Status);
		void setStage(Stage);
		void setStart(time_t);
		void setStop(time_t);

		const std::vector<Label>& getLabels() const;
		void addLabel(const Label&);

		const std::vector<Link>& getLinks() const;
		void addLink(const Link&);

		std::vector<TestCase>& getTestCases();
		const std::vector<TestCase>& getTestCases() const;
		void addTestCase(const TestCase&);
		void clearTestCases();

		virtual TestSuite& operator= (const TestSuite&);
		friend bool operator== (const TestSuite& lhs, const TestSuite& rhs);
		friend bool operator!= (const TestSuite& lhs, const TestSuite& rhs);

	private:
		std::string m_uuid;
		std::string m_name;
		std::string m_tmsId;
		Status m_status;
		Stage m_stage;
		time_t m_start;
		time_t m_stop;

		std::vector<Label> m_labels;
		std::vector<Link> m_links;
		std::vector<TestCase> m_testCases;
	};

}}}
