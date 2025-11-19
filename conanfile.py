import os
from pathlib import Path

from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy
from conan.errors import ConanInvalidConfiguration

required_conan_version = ">=2.0"

class Deps(ConanFile):
    name = "deps"

    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("imgui/1.92.4-docking")
        self.requires("glfw/[~3.3]")
        self.requires("glm/[~0.9]")
        self.requires("spdlog/1.16.0") #, options={"header_only": True})
        self.requires("fmt/12.0.0")
        self.requires("glad/[~0.1]")
        self.requires("gtest/1.17.0")

    def layout(self):
        cmake_layout(self)

    def configure(self):
        self.options["imgui"].with_glfw = True
        self.options["imgui"].with_opengl3 = True

        self.options["spdlog"].header_only = True
        self.options["spdlog"].fmt_external = False

    def generate(self):
        imgui = self.dependencies.get("imgui")
        if not imgui:
            return

        bindings_src = os.path.join(imgui.package_folder, "res", "bindings")
        bindings_dst = os.path.join(self.build_folder, "bindings")

        copy(self, "*glfw*", src=bindings_src, dst=bindings_dst)
        copy(self, "*opengl3*", src=bindings_src, dst=bindings_dst)
        copy(self, "*metal*", src=bindings_src, dst=bindings_dst)

        # If we want backends next to the generated CMake files instead:
        # bindings_dst = os.path.join(self.generators_folder, "bindings")

    def validate(self):
        cppstd = self.settings.get_safe("compiler.cppstd")
        if cppstd is None:
            raise ConanInvalidConfiguration(
                "compiler.cppstd must be set (e.g. 23 or gnu23) to build this project"
            )

        if "23" not in str(cppstd) and "20" not in str(cppstd):
            raise ConanInvalidConfiguration(
                f"Project requires at least C++20 (got '{cppstd}'). "
                "Please set compiler.cppstd=20 or compiler.cppstd=23 in your profile."
            )