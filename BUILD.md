# Build from sources

## Prerequisites
  - [Git](https://git-scm.com/)
  - [Conan](https://conan.io/)
  - [CMake](https://cmake.org/)
  - [Visual Studio](https://visualstudio.microsoft.com/) (only on Windows)

## Build steps
### Windows
With your desired configuration (Debug, Release), architecture (x86, x86_64) and package info (version from tag, channel stable or testing).
As example (config Release, arch x86_64, version 1.1.0, channel stable):

``` bash
> git clone https://github.com/systelab/cpp-gtest-allure-utilities
> md  && cd build-Release-x86_64
> conan install . --install-folder build-Release-x86_64 --profile=vs2022.conanprofile -s build_type=Release -s arch=x86_64
> conan build . --build-folder build-Release-x86_64
> conan export-pkg . GTestAllureUtilities/1.1.0@systelab/stable --profile=vs2022.conanprofile -s build_type=Release -s arch=x86_64 --force
```

### Others
By creating your own profile or tweaking conan settings you can build it for Linux and/or with another compiler.
Refer to Conan documentation (https://docs.conan.io/1/reference.html) for more details.