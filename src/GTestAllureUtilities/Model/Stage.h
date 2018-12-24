#pragma once


namespace systelab { namespace gtest_allure_utilities { namespace model {

	enum class Stage
	{
		PENDING = 0,
		SCHEDULED = 1,
		RUNNING = 2,
		FINISHED = 3,
		INTERRUPTED = 4
	};

}}}
