#include "GTestAllureUtilities/AllureAPI.h"
#include "GTestAllureUtilities/Model/TestSuite.h"

#include "TestUtilities/Stubs/Services/StubEventListener.h"
#include "TestUtilities/Stubs/Services/StubServicesFactory.h"
#include "TestUtilities/Stubs/Services/System/StubFileService.h"


using namespace testing;
using namespace systelab::gtest_allure_utilities;
using namespace systelab::gtest_allure_utilities::test_utility;

namespace systelab { namespace gtest_allure_utilities { namespace unit_test {

	class BaseIntegrationTest
	{
	public:
		BaseIntegrationTest();
		virtual ~BaseIntegrationTest() = default;

		void SetUp();

		void setCurrentTime(time_t);
		void setNextUUIDToGenerate(const std::string&);
		StubEventListener& getEventListener() const;

		size_t getSavedFilesCount() const;
		StubFile getSavedFile(unsigned int index) const;

	protected:
		void setUpServicesFactory();
		void setUpUUIDGeneratorService();
		void setUpTimeService();
		void setUpFileService();

	private:
		std::unique_ptr<StubServicesFactory> m_servicesFactory;
		std::unique_ptr<StubEventListener> m_eventListener;

		time_t m_currentTime;
		std::string m_nextUUIDToGenerate;
		std::vector<StubFile> m_savedFiles;
	};

}}}
