#pragma once


namespace systelab { namespace gtest_allure_utilities { namespace service {

	class ITestProgramStartEventHandler
	{
	public:
		virtual ~ITestProgramStartEventHandler() = default;

		virtual void handleTestProgramStart() const = 0;
	};

}}}
