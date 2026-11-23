# Build from sources

## Prerequisites
  - [Git](https://git-scm.com/)
  - [Conan](https://conan.io/)
  - [CMake](https://cmake.org/)
  - [Visual Studio](https://visualstudio.microsoft.com/) (only on Windows)

## Build steps
### Windows
With your desired configuration (Debug, Release), architecture (x86, x86_64) and version (from tag).
As example (config Release, arch x86_64, version 1.1.0):

``` bash
> git clone https://github.com/systelab/cpp-gtest-allure-utilities
> conan install . --output-folder build-Release-x86_64 -pr:a vs2022.conanprofile -s:h build_type=Release -s:b build_type=Release -s:h arch=x86_64
> conan build . --output-folder build-Release-x86_64 -pr:a vs2022.conanprofile -s:h build_type=Release -s:b build_type=Release -s:h arch=x86_64
> conan export-pkg . --version 1.1.0 --output-folder build-Release-x86_64 -pr:a vs2022.conanprofile -s:h build_type=Release -s:b build_type=Release -s:h arch=x86_64
```

### Others
By creating your own profile or tweaking conan settings you can build it for Linux and/or with another compiler.
Refer to [Conan documentation](https://docs.conan.io/2/reference.html) for more details.