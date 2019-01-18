#include "TestCase.h"


namespace systelab { namespace gtest_allure_utilities { namespace model {

	TestCase::TestCase()
		:m_uuid("")
		,m_historyId("")
		,m_name("")
		,m_description("")
		,m_status(Status::UNKNOWN)
		,m_stage(Stage::PENDING)
		,m_start(0)
		,m_stop(0)
		,m_labels()
		,m_links()
		,m_actions()
	{
	}

	TestCase::TestCase(const TestCase& other)
		:m_uuid(other.m_uuid)
		,m_historyId(other.m_historyId)
		,m_name(other.m_name)
		,m_description(other.m_description)
		,m_status(other.m_status)
		,m_stage(other.m_stage)
		,m_start(other.m_start)
		,m_stop(other.m_stop)
		,m_labels(other.m_labels)
		,m_links(other.m_links)
		,m_actions(other.m_actions)
	{
	}

	std::string TestCase::getUUID() const
	{
		return m_uuid;
	}

	std::string TestCase::getHistoryId() const
	{
		return m_historyId;
	}

	std::string TestCase::getName() const
	{
		return m_name;
	}

	std::string TestCase::getDescription() const
	{
		return m_description;
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

	void TestCase::setUUID(const std::string& uuid)
	{
		m_uuid = uuid;
	}

	void TestCase::setHistoryId(const std::string& historyId)
	{
		m_historyId = historyId;
	}

	void TestCase::setName(const std::string& name)
	{
		m_name = name;
	}

	void TestCase::setDescription(const std::string& description)
	{
		m_description = description;
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

	const std::vector<Label>& TestCase::getLabels() const
	{
		return m_labels;
	}

	void TestCase::addLabel(const Label& label)
	{
		m_labels.push_back(label);
	}

	const std::vector<Link>& TestCase::getLinks() const
	{
		return m_links;
	}

	void TestCase::addLink(const Link& link)
	{
		m_links.push_back(link);
	}

	const std::vector<Action>& TestCase::getActions() const
	{
		return m_actions;
	}

	void TestCase::addAction(const Action& action)
	{
		m_actions.push_back(action);
	}

	TestCase& TestCase::operator= (const TestCase& other)
	{
		m_uuid = other.m_uuid;
		m_historyId = other.m_historyId;
		m_name = other.m_name;
		m_description = other.m_description;
		m_status = other.m_status;
		m_stage = other.m_stage;
		m_start = other.m_start;
		m_stop = other.m_stop;
		m_labels = other.m_labels;
		m_links = other.m_links;
		m_actions = other.m_actions;

		return *this;
	}

	bool operator== (const TestCase& lhs, const TestCase& rhs)
	{
		return (lhs.m_uuid == rhs.m_uuid) &&
			   (lhs.m_historyId == rhs.m_historyId) &&
			   (lhs.m_name == rhs.m_name) &&
			   (lhs.m_description == rhs.m_description) &&
			   (lhs.m_status == rhs.m_status) &&
			   (lhs.m_stage == rhs.m_stage) &&
			   (lhs.m_start == rhs.m_start) &&
			   (lhs.m_stop == rhs.m_stop) &&
			   (lhs.m_labels == rhs.m_labels) &&
			   (lhs.m_links == rhs.m_links) &&
			   (lhs.m_actions == rhs.m_actions);
	}

	bool operator!= (const TestCase& lhs, const TestCase& rhs)
	{
		return !(lhs == rhs);
	}

}}}