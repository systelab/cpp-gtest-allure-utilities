from conans import ConanFile, tools

class GTestAllureUtilitiesConan(ConanFile):
    name = "GTestAllureUtilities"
    description = "Allure reporting utilities for Google Test"
    url = "https://github.com/systelab/cpp-gtest-allure-utilities"
    homepage = "https://github.com/systelab/cpp-gtest-allure-utilities"
    author = "CSW <csw@werfen.com>"
    topics = ("conan", "allure", "gtest", "json")	
    license = "MIT"
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("rapidjson/1.1.0@bincrafters/stable")

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")

    def package(self):
        self.copy("GTestAllureUtilities.h", dst="include/GTestAllureUtilities", src="src/GTestAllureUtilities")
        self.copy("*GTestAllureUtilities.lib", dst="lib", keep_path=False)
        self.copy("*GTestAllureUtilities.pdb", dst="lib", keep_path=False)
        self.copy("*GTestAllureUtilities.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
