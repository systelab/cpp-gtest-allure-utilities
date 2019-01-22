#pragma once

#include "ITestProgramStartEventHandler.h"

#include <memory>


namespace systelab { namespace gtest_allure_utilities { namespace model {
	class TestSuite;
}}}

namespace systelab { namespace gtest_allure_utilities { namespace service {

	class TestProgramStartEventHandler : public ITestProgramStartEventHandler
	{
	public:
		TestProgramStartEventHandler(model::TestSuite&);
		virtual ~TestProgramStartEventHandler() = default;

		void handleTestProgramStart() const;

	private:
		model::TestSuite& m_testSuite;
	};

}}}
