#include "TestSuiteEndEventHandler.h"

#include "Model/TestProgram.h"
#include "Services/System/ITimeService.h"

#include <regex>


namespace systelab { namespace gtest_allure { namespace service {

	TestSuiteEndEventHandler::TestSuiteEndEventHandler(model::TestProgram& testProgram,
													   std::unique_ptr<ITimeService> timeService)
		:m_testProgram(testProgram)
		,m_timeService(std::move(timeService))
	{
	}

	void TestSuiteEndEventHandler::handleTestSuiteEnd(model::Status status) const
	{
		model::TestSuite& testSuite = getRunningTestSuite();
		testSuite.setStop(m_timeService->getCurrentTime());
		testSuite.setStage(model::Stage::FINISHED);
		testSuite.setStatus(status);
		addTMSLink(testSuite);
	}

	model::TestSuite& TestSuiteEndEventHandler::getRunningTestSuite() const
	{
		unsigned int nTestSuites = (unsigned int) m_testProgram.getTestSuitesCount();
		for (unsigned int i = 0; i < nTestSuites; i++)
		{
			model::TestSuite& testSuite = m_testProgram.getTestSuite(i);
			if (testSuite.getStage() == model::Stage::RUNNING)
			{
				return testSuite;
			}
		}

		throw NoRunningTestSuiteException();
	}

	void TestSuiteEndEventHandler::addTMSLink(model::TestSuite& testSuite) const
	{
		auto tmsId = testSuite.getTmsId();
		auto tmsLinksPattern = m_testProgram.getTMSLinksPattern();
		auto tmsURL = tmsLinksPattern.replace(tmsLinksPattern.find("{}"), 2, tmsId);

		model::Link tmsLink;
		tmsLink.setName(tmsId);
		tmsLink.setURL(tmsURL);
		tmsLink.setType("tms");
		testSuite.addLink(tmsLink);
	}

}}}
