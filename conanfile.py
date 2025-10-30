import os
from pathlib import Path

from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy

required_conan_version = ">=2.0"

class Deps(ConanFile):
    name = "deps"

    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("imgui/[~1.89]")
        self.requires("glfw/[~3.3]")
        self.requires("glm/[~0.9]")
        self.requires("spdlog/1.16.0", options={"header_only": True})
        self.requires("glad/[~0.1]")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        imgui = self.dependencies.get("imgui")
        if not imgui:
            return

        bindings_src = os.path.join(imgui.package_folder, "res", "bindings")
        bindings_dst = os.path.join(self.build_folder, "bindings")

        copy(self, "*glfw*", src=bindings_src, dst=bindings_dst)
        copy(self, "*opengl3*", src=bindings_src, dst=bindings_dst)

        # If we want backends next to the generated CMake files instead:
        # bindings_dst = os.path.join(self.generators_folder, "bindings")
