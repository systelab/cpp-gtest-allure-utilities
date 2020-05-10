#pragma once

#include "ITestProgramEndEventHandler.h"

#include <memory>


namespace systelab { namespace gtest_allure { namespace model {
	class TestProgram;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class ITestProgramJSONBuilder;

	class TestProgramEndEventHandler : public ITestProgramEndEventHandler
	{
	public:
		TestProgramEndEventHandler(model::TestProgram&,
								   std::unique_ptr<ITestProgramJSONBuilder>);
		virtual ~TestProgramEndEventHandler() = default;

		void handleTestProgramEnd() const;

	private:
		model::TestProgram& m_testProgram;
		std::unique_ptr<ITestProgramJSONBuilder> m_testProgramJSONBuilderService;
	};

}}}
