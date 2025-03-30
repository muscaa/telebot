from conan import ConanFile
from conan.tools.cmake import cmake_layout

class CompressorRecipe(ConanFile):
    settings = ("os", "compiler", "build_type", "arch")
    generators = ("CMakeToolchain", "CMakeDeps")

    def requirements(self):
        self.requires("sdl/3.2.6")

    def build_requirements(self):
        self.tool_requires("cmake/3.31.6")

    def layout(self):
        cmake_layout(self)
