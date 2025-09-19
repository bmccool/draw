import os

from conan import ConanFile
from conan.tools.microsoft import MSBuildToolchain, MSBuild, vs_layout
from conan.tools.files import copy


class drawConan(ConanFile):
    name = "draw"
    version = "0.1.1"

    # Binary configuration
    package_type = "static-library" # hardcoded in .vcxproj
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "draw.sln", "draw.vcxproj", "src/*", "include/*"

    def layout(self):
        vs_layout(self)

    def generate(self):
        tc = MSBuildToolchain(self)
        tc.generate()

    def build(self):
        msbuild = MSBuild(self)
        msbuild.build("draw.sln")

    def package(self):
        copy(self, "*.h", os.path.join(self.source_folder, "include"),
             dst=os.path.join(self.package_folder, "include"))
        copy(self, "*.lib", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"),
             keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["draw"]
