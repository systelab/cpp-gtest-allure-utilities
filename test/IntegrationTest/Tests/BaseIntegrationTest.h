#include "GTestAllureUtilities/AllureAPI.h"
#include "GTestAllureUtilities/Model/TestSuite.h"

#include "RapidJSONAdapter/JSONAdapter.h"

#include "TestUtilities/Stubs/Services/StubEventListener.h"
#include "TestUtilities/Stubs/Services/StubServicesFactory.h"
#include "TestUtilities/Stubs/Services/System/StubFileService.h"


using namespace testing;
using namespace systelab::gtest_allure;
using namespace systelab::gtest_allure::test_utility;

namespace systelab { namespace gtest_allure { namespace unit_test {

	class BaseIntegrationTest
	{
	public:
		BaseIntegrationTest();
		virtual ~BaseIntegrationTest() = default;

		void SetUp();
		void TearDown();

		void setCurrentTime(time_t);
		void setNextUUIDToGenerate(const std::string&);
		StubEventListener& getEventListener() const;

		size_t getSavedFilesCount() const;
		StubFile getSavedFile(unsigned int index) const;

		const json::IJSONAdapter& getJSONAdapter() const;

	protected:
		void setUpServicesFactory();
		void setUpUUIDGeneratorService(StubServicesFactory&);
		void setUpTimeService(StubServicesFactory&);
		void setUpFileService(StubServicesFactory&);

	private:
		std::unique_ptr<StubEventListener> m_eventListener;

		time_t m_currentTime;
		std::string m_nextUUIDToGenerate;
		std::vector<StubFile> m_savedFiles;

		const json::rapidjson::JSONAdapter m_jsonAdapter;
	};

}}}
