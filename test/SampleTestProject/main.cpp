#include "stdafx.h"
#include "GTestAllureUtilities/AllureAPI.h"


int main(int argc, char* argv[])
{
	::testing::FLAGS_gmock_verbose = "error";
	::testing::InitGoogleTest(&argc, argv);

	systelab::gtest_allure::AllureAPI::setTestProgramName("SampleTestProject");
	systelab::gtest_allure::AllureAPI::setOutputFolder("Reports/Allure");
	
	::testing::UnitTest::GetInstance()->listeners().Append(systelab::gtest_allure::AllureAPI::buildListener().release());

	int res = RUN_ALL_TESTS();

	return res;
}
