#pragma once


namespace systelab { namespace gtest_allure { namespace service {

	class ITestProgramEndEventHandler
	{
	public:
		virtual ~ITestProgramEndEventHandler() = default;

		virtual void handleTestProgramEnd() const = 0;
	};

}}}
