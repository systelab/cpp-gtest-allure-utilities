[![Build Status](https://travis-ci.org/systelab/cpp-gtest-allure-utilities.svg?branch=master)](https://travis-ci.org/systelab/cpp-gtest-allure-utilities)
[![Build status](https://ci.appveyor.com/api/projects/status/srstqtis5eoo3y1r?svg=true)](https://ci.appveyor.com/project/systelab/cpp-gtest-allure-utilities)
[![codecov](https://codecov.io/gh/systelab/cpp-gtest-allure-utilities/branch/master/graph/badge.svg)](https://codecov.io/gh/systelab/cpp-gtest-allure-utilities)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e741aa9726794fe182f2629a31df5deb)](https://www.codacy.com/app/joaquimvila/cpp-gtest-allure-utilities?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=systelab/cpp-gtest-allure-utilities&amp;utm_campaign=Badge_Grade)
[![Download](https://api.bintray.com/packages/systelab/conan/GTestAllureUtilities:systelab/images/download.svg)](https://bintray.com/systelab/conan/GTestAllureUtilities:systelab/_latestVersion)


# C++ Allure utilities for GTest

Utilities to generate [Allure](http://allure.qatools.ru/) reports for automated tests based on [GoogleTest](https://github.com/google/googletest).

## Setup

### Build from sources

Prerequisites:
  - [Git](https://git-scm.com/)
  - [Conan](https://conan.io/)
  - [CMake](https://cmake.org/)
  - [Visual Studio](https://visualstudio.microsoft.com/) (only on Windows)
  - [GCC](https://gcc.gnu.org/) (only on Linux)

Build library with the following steps:
  1. Clone this repository in a local drive
  2. Make a build directory (i.e. `build/`)
  3. Install `conan` dependencies in the build directory
  4. Run `cmake` in the build directory to configure build targets
  5. Use `Visual Studio` (on Windows) or `make` (on Linux) to build the library

#### Windows

In order to build the application on Windows for the `Release` configuration, run the following commands ($VSINSTALLPATH is the path where Visual Studio has been installed):

``` bash
> git clone https://github.com/systelab/cpp-gtest-allure-utilities
> md build && cd build
> conan remote add systelab-bintray https://api.bintray.com/conan/systelab/conan
> conan install .. -s build_type=Release -s compiler.toolset=v142 -s arch=x86_64
> cmake .. -G "Visual Studio 16 2019" -A x64
> "$VSINSTALLPATH/devenv.com" JSONSettings.sln /build "Release" /PROJECT "GTestAllureUtilities"
```

However, if you want to `Debug` the source code, you will need these commands:

``` bash
> git clone https://github.com/systelab/cpp-gtest-allure-utilities
> md build && cd build
> conan remote add systelab-bintray https://api.bintray.com/conan/systelab/conan
> conan install .. -s build_type=Debug -s compiler.toolset=v142 -s arch=x86_64
> cmake .. -G "Visual Studio 16 2019" -A x64
> "$VSINSTALLPATH/devenv.com" JSONSettings.sln /build "Debug" /PROJECT "GTestAllureUtilities"
```

#### Linux
``` bash
> git clone https://github.com/systelab/cpp-gtest-allure-utilities
> mkdir build && cd build
> conan install ..
> cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
> make
```

### Download using Conan

  1. Create/update your `conanfile.txt` to add this library as follows:

```
[requires]
GTestAllureUtilities/1.0.0@systelab/stable

[generators]
cmake
```

> Version number of this code snipped is set just an example. Replace it for the desired package to retrieve.

  2. Integrate Conan into CMake by adding the following code into your `CMakeLists.txt`:

```cmake
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
```

  3. Link against `${CONAN_LIBS}` when configuring your executables in CMake:

```cmake
set(MY_PROJECT MyProject)
add_executable(${MY_PROJECT} main.cpp)
target_link_libraries(${MY_PROJECT} ${CONAN_LIBS})
```

## Usage

```
TBD
```
