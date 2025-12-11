from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps
from conan.tools.files import copy, collect_libs
import os

class GTestAllureUtilitiesConan(ConanFile):
    name = "gtest-allure-utilities"
    description = "Allure reporting utilities for Google Test"
    url = "https://github.com/systelab/cpp-gtest-allure-utilities"
    homepage = "https://github.com/systelab/cpp-gtest-allure-utilities"
    author = "CSW <csw@werfen.com>"
    topics = ("conan", "allure", "gtest", "json")
    license = "MIT"

    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "src/*"
    
    def requirements(self):
        self.tool_requires("gtest/1.14.0")
        self.requires("rapidjson/1.2.0")
        self.requires("json-adapter-interface/1.2.0")
        self.requires("rapidjson-adapter/1.2.0")

    def build_requirements(self):
        self.tool_requires("rapidjson/1.2.0")
        self.tool_requires("json-adapter-test-utilities/1.2.0")
        self.test_requires("json-adapter-test-utilities/1.2.0")
        self.test_requires("gtest/1.14.0")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

        bin_dst = os.path.join(self.build_folder, "bin")

        for dep in self.dependencies.values():
            for bindir in dep.cpp_info.bindirs:
                copy(self, "*.dll", dst=bin_dst, src=bindir)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        
        include_src = os.path.join(self.source_folder, "src", "GTestAllureUtilities")
        include_src_model = os.path.join(include_src, "Model")
        include_dst = os.path.join(self.package_folder, "include", "GTestAllureUtilities")
        include_dst_model = os.path.join(include_dst, "Model")
        
        copy(self, "AllureAPI.h",   dst=include_dst, src=include_src)
        copy(self, "*.h",           dst=include_dst_model, src=include_src_model)
        
        lib_src = os.path.join(self.build_folder, "lib", str(self.settings.build_type))
        lib_dst = os.path.join(self.package_folder, "lib")
        
        copy(self, "*.lib", dst=lib_dst, src=lib_src, keep_path=False)
        copy(self, "*.pdb", dst=lib_dst, src=lib_src, keep_path=False)

    def package_info(self):
        self.cpp_info.libs = collect_libs(self)