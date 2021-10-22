from conans import ConanFile, tools

class GTestAllureUtilitiesConan(ConanFile):
    name = "GTestAllureUtilities"
    description = "Allure reporting utilities for Google Test"
    url = "https://github.com/systelab/cpp-gtest-allure-utilities"
    homepage = "https://github.com/systelab/cpp-gtest-allure-utilities"
    author = "CSW <csw@werfen.com>"
    topics = ("conan", "allure", "gtest", "json")	
    license = "MIT"
    generators = "cmake_find_package"
    settings = "os", "compiler", "build_type", "arch"
    options = {"gtest": ["1.10.0"]}
    default_options = {"gtest":"1.10.0"}
    exports_sources = "*","!build"

    def configure(self):
        self.options["RapidJSONAdapter"].gtest = self.options.gtest
        self.options["JSONAdapterTestUtilities"].gtest = self.options.gtest

    def requirements(self):
        self.requires("RapidJSONAdapter/1.1.6@systelab/stable")
        self.requires("gtest/1.10.0#0c895f60b461f8fee0da53a84d659131")

    def build_requirements(self):
        self.build_requires("JSONAdapterTestUtilities/1.1.5@systelab/stable")

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder=".")
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")

    def package(self):
        self.copy("AllureAPI.h", dst="include/GTestAllureUtilities", src="src/GTestAllureUtilities")
        self.copy("*.h", dst="include/GTestAllureUtilities/Model", src="src/GTestAllureUtilities/Model")
        self.copy("*GTestAllureUtilities.lib", dst="lib", keep_path=False)
        self.copy("*GTestAllureUtilities.pdb", dst="lib", keep_path=False)
        self.copy("*GTestAllureUtilities.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
