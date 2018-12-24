#pragma once


namespace systelab { namespace gtest_allure_utilities { namespace model {

	enum class Status
	{
		UNKNOWN = 0,
		PASSED = 1,
		FAILED = 2,
		BROKEN = 3,
		SKIPPED = 4
	};

}}}
