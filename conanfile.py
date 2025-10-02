from posixpath import join
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy


class drawRecipe(ConanFile):
    name = "draw"
    version = "0.2.3"
    package_type = "library"

    # Optional metadata
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of draw package here>"
    topics = ("<Put some tag here>", "<here>", "<and here>")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "include*"
    
    def requirements(self):
        self.requires("cmocka/1.1.8", test=True)

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        print("===================================================================================")
        print("Copying header files...")
        print(f"From: {join(self.source_folder, 'include')} To: {join(self.package_folder, 'include')}")
        copy(self, "*.h", join(self.source_folder, "include"), join(self.package_folder, "include"))
        copy(self, "*.c", join(self.source_folder, "src"), join(self.package_folder, "src"))
        copy(self, "*.lib", src=join(self.build_folder, "lib"), dst=join(self.package_folder, "lib"))

    def package_info(self):
        self.cpp_info.libs = ["draw"]
        self.cpp_info.libdirs = ["lib"]
        self.cpp_info.srcdirs = ["src"]

