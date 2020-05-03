#pragma once


namespace systelab { namespace gtest_allure { namespace service {

	class ITestProgramStartEventHandler
	{
	public:
		virtual ~ITestProgramStartEventHandler() = default;

		virtual void handleTestProgramStart() const = 0;
	};

}}}
