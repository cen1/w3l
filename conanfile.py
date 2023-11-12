from conan import ConanFile
from conan.tools.files import copy

class w3l(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    requires = (
        "cpp-httplib/0.14.1",
        "nlohmann_json/3.11.2",
        "zlib/1.3",
        "openssl/3.1.4",
    )

    default_options = {
        "*:shared": True,
        "pkg/cpp-httplib:with_openssl": True,
        "pkg/cpp-httplib:with_zlib": True,
    }

    def generate(self):
        for dep in self.dependencies.values():
            if dep.cpp_info.libdirs:
                copy(self, "*.lib", dep.cpp_info.libdirs[0], self.build_folder)
            if dep.cpp_info.bindirs:
                copy(self, "*.dll", dep.cpp_info.bindirs[0], self.build_folder)