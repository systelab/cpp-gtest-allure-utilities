#include "TestSuite.h"


namespace systelab { namespace gtest_allure { namespace model {

	TestSuite::TestSuite()
		:m_uuid()
		,m_name()
		,m_status(Status::UNKNOWN)
		,m_stage(Stage::PENDING)
		,m_start(0)
		,m_stop(0)
		,m_labels()
		,m_links()
		,m_testCases()
	{
	}

	TestSuite::TestSuite(const TestSuite& other)
		:m_uuid(other.m_uuid)
		,m_name(other.m_name)
		,m_status(other.m_status)
		,m_stage(other.m_stage)
		,m_start(other.m_start)
		,m_stop(other.m_stop)
		,m_labels(other.m_labels)
		,m_links(other.m_links)
		,m_testCases(other.m_testCases)
	{
	}

	std::string TestSuite::getUUID() const
	{
		return m_uuid;
	}

	std::string TestSuite::getName() const
	{
		return m_name;
	}

	Status TestSuite::getStatus() const
	{
		return m_status;
	}

	Stage TestSuite::getStage() const
	{
		return m_stage;
	}

	time_t TestSuite::getStart() const
	{
		return m_start;
	}

	time_t TestSuite::getStop() const
	{
		return m_stop;
	}

	void TestSuite::setName(const std::string& name)
	{
		m_name = name;
	}

	void TestSuite::setUUID(const std::string& uuid)
	{
		m_uuid = uuid;
	}

	void TestSuite::setStatus(Status status)
	{
		m_status = status;
	}

	void TestSuite::setStage(Stage stage)
	{
		m_stage = stage;
	}

	void TestSuite::setStart(time_t start)
	{
		m_start = start;
	}

	void TestSuite::setStop(time_t stop)
	{
		m_stop = stop;
	}

	const std::vector<Label>& TestSuite::getLabels() const
	{
		return m_labels;
	}

	void TestSuite::addLabel(const Label& label)
	{
		m_labels.push_back(label);
	}

	const std::vector<Link>& TestSuite::getLinks() const
	{
		return m_links;
	}

	void TestSuite::addLink(const Link& link)
	{
		m_links.push_back(link);
	}

	std::vector<TestCase>& TestSuite::getTestCases()
	{
		return m_testCases;
	}

	const std::vector<TestCase>& TestSuite::getTestCases() const
	{
		return m_testCases;
	}

	void TestSuite::addTestCase(const TestCase& testCase)
	{
		m_testCases.push_back(testCase);
	}

	void TestSuite::clearTestCases()
	{
		m_testCases.clear();
	}

	TestSuite& TestSuite::operator= (const TestSuite& other)
	{
		m_uuid = other.m_uuid;
		m_name = other.m_name;
		m_status = other.m_status;
		m_stage = other.m_stage;
		m_start = other.m_start;
		m_stop = other.m_stop;

		m_labels = other.m_labels;
		m_links = other.m_links;
		m_testCases = other.m_testCases;

		return *this;
	}

	bool operator== (const TestSuite& lhs, const TestSuite& rhs)
	{
		return (lhs.m_uuid == rhs.m_uuid) &&
			   (lhs.m_name == rhs.m_name) &&
			   (lhs.m_status == rhs.m_status) &&
			   (lhs.m_stage == rhs.m_stage) &&
			   (lhs.m_start == rhs.m_start) &&
			   (lhs.m_stop == rhs.m_stop) &&
			   (lhs.m_labels == rhs.m_labels) &&
			   (lhs.m_links == rhs.m_links) &&
			   (lhs.m_testCases == rhs.m_testCases);
	}

	bool operator!= (const TestSuite& lhs, const TestSuite& rhs)
	{
		return !(lhs == rhs);
	}

}}}