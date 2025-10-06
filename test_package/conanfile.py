import os

from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.build import can_run
from conan.tools.files import copy


class drawTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        print("REQUIREMENTS!!!!!!!!!!!------------")
        print(f"Reference is {self.tested_reference_str}")
        self.requires(self.tested_reference_str)
        self.requires("cmocka/1.1.8", test=True)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        #cmake.build(cli_args=["--verbose"])
        cmake.build()

    def layout(self):
        cmake_layout(self)

    def test(self):
        if can_run(self):
            cmd = os.path.join(self.cpp.build.bindir, "example")
            self.run(cmd, env="conanrun")
