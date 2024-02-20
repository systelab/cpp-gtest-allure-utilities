from conans import ConanFile, CMake, tools

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
	exports_sources = "*","!build-*"

	def requirements(self):
		self.requires("RapidJSONAdapter/1.1.6@systelab/stable")
		self.requires("gtest/1.14.0#4372c5aed2b4018ed9f9da3e218d18b3")
		self.requires("JSONAdapterTestUtilities/1.1.5@systelab/stable", private=True)

	def build(self):
		cmake = CMake(self)
		cmake.configure(source_folder=".")
		cmake.build()

	def imports(self):
		self.copy("*.dll", dst="bin", src="bin")

	def package(self):
		self.copy("AllureAPI.h", dst="include/GTestAllureUtilities", src="src/GTestAllureUtilities")
		self.copy("*.h", dst="include/GTestAllureUtilities/Model", src="src/GTestAllureUtilities/Model")
		self.copy("*GTestAllureUtilities.lib", dst="lib", keep_path=False)
		self.copy("*GTestAllureUtilities.pdb", dst="lib", keep_path=False)

	def package_info(self):
		self.cpp_info.libs = tools.collect_libs(self)
