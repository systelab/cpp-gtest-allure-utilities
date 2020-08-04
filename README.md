[![Build Status](https://travis-ci.org/systelab/cpp-gtest-allure-utilities.svg?branch=master)](https://travis-ci.org/systelab/cpp-gtest-allure-utilities)
[![Build status](https://ci.appveyor.com/api/projects/status/srstqtis5eoo3y1r?svg=true)](https://ci.appveyor.com/project/systelab/cpp-gtest-allure-utilities)
[![codecov](https://codecov.io/gh/systelab/cpp-gtest-allure-utilities/branch/master/graph/badge.svg)](https://codecov.io/gh/systelab/cpp-gtest-allure-utilities)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e741aa9726794fe182f2629a31df5deb)](https://www.codacy.com/app/joaquimvila/cpp-gtest-allure-utilities?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=systelab/cpp-gtest-allure-utilities&amp;utm_campaign=Badge_Grade)
[![Download](https://api.bintray.com/packages/systelab/conan/GTestAllureUtilities:systelab/images/download.svg)](https://bintray.com/systelab/conan/GTestAllureUtilities:systelab/_latestVersion)


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
conan remote add systelab-bintray https://api.bintray.com/conan/systelab/conan 
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

By default, each test suite will be named as the associated test class. However, this name can be adjusted with the `AllureAPI::setTestSuiteName(...)` method. Similarly, the `AllureAPI::setTestSuiteDescription(...)` and `AllureAPI::setTMSId(...)` method allows setting the description and the TMS identifier of the test suite respectively.

```cpp
class MyTestSuite : public testing::Test
{
    static void SetUpTestSuite()
    {
        AllureAPI::setTestSuiteName("My test suite name"); // Without this line, test suite name would be "MyTestSuite"
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


### Add steps into a test case

```
TBD
```

### Add test suite labels

```
TBD
```

### Configure TMS links

```
TBD
```

### Examples

See [Sample Test project](test/SampleTestProject) for more complete usage examples.
