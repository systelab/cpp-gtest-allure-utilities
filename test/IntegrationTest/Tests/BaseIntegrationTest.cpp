#include "stdafx.h"
#include "BaseIntegrationTest.h"

#include "TestUtilities/Mocks/Services/System/MockTimeService.h"
#include "TestUtilities/Mocks/Services/System/MockUUIDGeneratorService.h"

#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;
using namespace systelab::json::test_utility;

namespace systelab { namespace gtest_allure { namespace unit_test {

	BaseIntegrationTest::BaseIntegrationTest()
		:m_currentTime(0)
	{
	}

	void BaseIntegrationTest::SetUp()
	{
		setUpServicesFactory();
		m_eventListener = std::unique_ptr<StubEventListener>(new StubEventListener(*m_servicesFactory));
	}

	void BaseIntegrationTest::setCurrentTime(time_t currentTime)
	{
		m_currentTime = currentTime;
	}

	void BaseIntegrationTest::setNextUUIDToGenerate(const std::string& nextUUIDToGenerate)
	{
		m_nextUUIDToGenerate = nextUUIDToGenerate;
	}

	StubEventListener& BaseIntegrationTest::getEventListener() const
	{
		return *m_eventListener;
	}

	size_t BaseIntegrationTest::getSavedFilesCount() const
	{
		return m_savedFiles.size();
	}

	StubFile BaseIntegrationTest::getSavedFile(unsigned int index) const
	{
		return m_savedFiles[index];
	}

	const json::IJSONAdapter& BaseIntegrationTest::getJSONAdapter() const
	{
		return m_jsonAdapter;
	}

	void BaseIntegrationTest::setUpServicesFactory()
	{
		model::TestProgram& testProgram = AllureAPI::getTestProgram();
		m_servicesFactory = std::unique_ptr<StubServicesFactory>(new StubServicesFactory(testProgram));

		setUpUUIDGeneratorService();
		setUpTimeService();
		setUpFileService();
	}

	void BaseIntegrationTest::setUpUUIDGeneratorService()
	{
		m_nextUUIDToGenerate = "";
		ON_CALL(*m_servicesFactory, buildUUIDGeneratorServiceProxy()).WillByDefault(Invoke(
			[this]() -> service::IUUIDGeneratorService*
			{
				auto uuidGeneratorService = new MockUUIDGeneratorService();
				ON_CALL(*uuidGeneratorService, generateUUID()).WillByDefault(Invoke(
					[this]() -> std::string
					{
						return m_nextUUIDToGenerate;
					}
				));
				return uuidGeneratorService;
			}
		));
	}

	void BaseIntegrationTest::setUpTimeService()
	{
		m_currentTime = 0;
		ON_CALL(*m_servicesFactory, buildTimeServiceProxy()).WillByDefault(Invoke(
			[this]() -> service::ITimeService*
			{
				auto timeService = new MockTimeService();
				ON_CALL(*timeService, getCurrentTime()).WillByDefault(Invoke(
					[this]() -> time_t
					{
						return m_currentTime;
					}
				));
				return timeService;
			}
		));
	}

	void BaseIntegrationTest::setUpFileService()
	{
		m_savedFiles.clear();
		ON_CALL(*m_servicesFactory, buildFileServiceProxy()).WillByDefault(Invoke(
			[this]() -> service::IFileService*
			{
				return new StubFileService(m_savedFiles);
			}
		));
	}

}}}
