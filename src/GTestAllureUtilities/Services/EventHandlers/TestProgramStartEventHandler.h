#pragma once

#include "ITestProgramStartEventHandler.h"

#include <memory>


namespace systelab { namespace gtest_allure { namespace model {
	class TestProgram;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class TestProgramStartEventHandler : public ITestProgramStartEventHandler
	{
	public:
		TestProgramStartEventHandler(model::TestProgram&);
		virtual ~TestProgramStartEventHandler();

		void handleTestProgramStart() const;

	private:
		model::TestProgram& m_testProgram;
	};

}}}
