[![codecov](https://codecov.io/gh/systelab/cpp-gtest-allure-utilities/branch/master/graph/badge.svg)](https://codecov.io/gh/systelab/cpp-gtest-allure-utilities)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/0235467f9ad346cea99fac3a743d0750)](https://www.codacy.com/gh/systelab/cpp-gtest-allure-utilities/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=systelab/cpp-gtest-allure-utilities&amp;utm_campaign=Badge_Grade)


# C++ Allure utilities for GoogleTest

Utilities to generate [Allure](http://allure.qatools.ru/) reports for automated tests based on [GoogleTest](https://github.com/google/googletest).


## Setup

### Download using Conan

This library is designed to be installed by making use of [Conan](https://conan.io/) package manager. So, you just need to add the following requirement into your Conan recipe:

```python
def requirements(self):
   self.requires("GTestAllureUtilities/1.0.0@systelab/stable")
```

> Version number of this code snipped is set just as an example. Replace it for the desired package to retrieve.

As this package is not available on the conan-center, you will also need to configure a remote repository before installing dependencies:

```bash
conan remote add systelab-public https://csw.jfrog.io/artifactory/api/conan/cpp-conan-production-local
```

See Conan [documentation](https://docs.conan.io/en/latest/) for further details on how to integrate this package with your build system.


### Build from sources

See [BUILD.md](BUILD.md) document for details.


## Usage

### Register library as a GoogleTest listener

This library needs to be registered as a listener of your GoogleTest program. This registering can be done as follows:

```cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GTestAllureUtilities/AllureAPI.h"

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	::testing::UnitTest::GetInstance()->listeners()
		.Append(systelab::gtest_allure::AllureAPI::buildListener().release());

	int res = RUN_ALL_TESTS();

	return res;
}
```


### Configure output folder

The folder where JSON Allure reports will be generated can be defined by using the `AllureAPI::setOutputFolder(...)` method:

```cpp
systelab::gtest_allure::AllureAPI::setOutputFolder("Allure/Reports/Folder");
```
> This needs to be configured before executing the `RUN_ALL_TESTS()` macro of GoogleTest.


### Set name, description and TMS identifier of test suite

By default, each test suite will be named as the associated test class. However, this name can be adjusted with the `AllureAPI::setTestSuiteName(...)` method. Similarly, the `AllureAPI::setTestSuiteDescription(...)` and `AllureAPI::setTMSId(...)` methods allow setting the description and the TMS identifier of the test suite respectively.

```cpp
class MyTestSuite : public testing::Test
{
    static void SetUpTestSuite()
    {
        AllureAPI::setTestSuiteName("My test suite name"); // Default test suite is "MyTestSuite"
        AllureAPI::setTestSuiteDescription("This is the description for the MyTestSuite");
        AllureAPI::setTMSId("TC-AT-PROJ-001");
    }
};
```


### Set test macro description

For each test macro (`TEST_F` or `TEST_P`) in a suite, an action step will be added to the generated report. By default, these actions will have the name of the test fixture assigned by GoogleTest as a description. This description can be overwritten by making use of the `AllureAPI::setTestCaseName(...)` method:

```cpp
TEST_F(MyTestSuite, testSomething)
{
   // Default action description is "MyTestSuite.testSomething" (automatically assigned by GoogleTest)
   AllureAPI::setTestCaseName("Human readable description of test action");
}
```


### Define steps for a test macro

When a test macro is quite complex, it might be interesting to decompose it into several steps. Moreover, some these steps will correspond with actions and the rest to expected results. So, in order to facilitate the definition of this kind of test scenarios, the library provides the `AllureAPI::addAction(...)` and `AllureAPI::addExpectedResult(...)` methods. They require 2 arguments: a human readable description of the step and a lambda function with the code included on the step.

The following example illustrates how to define a test macro with multiple steps:

```cpp
TEST_F(MyTestSuite, testSumOfValuesVector)
{
    AllureAPI::setTestCaseName("Compute sum of 5 + 3");
    int result = 5 + 3;
   
    AllureAPI::addExpectedResult("Sum result is equal to 8", [result]() -> void
    {
        ASSERT_EQ(8, result);
    });
    
    AllureAPI::addAction("Add 22 to result of previous sum", [&result]() -> void
    {
        result += 22;
    });
    
    AllureAPI::addExpectedResult("New sum result is equal to 30", [result]() -> void
    {
        ASSERT_EQ(30, result);
    }); 
}
```


### Add labels to a test suite

Labels allow complementing the general information defined for each test suite. They can be recorded through the `AllureAPI::setTestSuiteLabel(...)` method. Additionally, the library provides built-in methods to include the most common labels. 

```cpp
class MyTestSuite : public testing::Test
{
    static void SetUpTestSuite()
    {
    	// ...
	
	// Add built-in labels
        AllureAPI::setTestSuiteEpic("Epic name of test suite");
        AllureAPI::setTestSuiteSeverity("high");
	
	// Add custom labels
        AllureAPI::setTestSuiteLabel("CustomLabel1", "Value for custom label 1");
        AllureAPI::setTestSuiteLabel("CustomLabel2", "Value for custom label 2");
    }
};
```

> Labels are designed to be unique per test suite. Thus, if a label is set twice on the same suite, then only the latest value provided will be included on the report.

### Additional test program options

#### Program name

The name of the test program (included in filename of generated report files) can be adjusted as follows:

```cpp
systelab::gtest_allure::AllureAPI::setTestProgramName("MyTestProjectName");
```

#### TMS Link patterns

The pattern of the links between each test suite and the test management system (TMS) needs to be configured before starting the test program:

```cpp
systelab::gtest_allure::AllureAPI::setTMSLinksPattern("https://mycompany.com/tms/{}");
```
> The `{}` will be replaced by the TMS identifier on the report of each test suite


### Examples

See [Sample Test project](test/SampleTestProject) for more complete usage examples.
