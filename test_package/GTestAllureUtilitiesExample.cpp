#include "GTestAllureUtilities/AllureAPI.h"

#include <iostream>


int main(int argc, char *argv[])
{
    auto listener = systelab::gtest_allure::AllureAPI.buildListener();
	std::cout << "Listener successfully built!" << std::endl;

    return 0;
}
