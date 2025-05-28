from utils.package import *
from utils import platform

NAME: str = "telebot"

PACKAGE_EXECUTABLE: Executable = Executable("telebot")
PACKAGE_LIBRARIES: list[Lib] = [
]
PACKAGE_OTHER: list[File] = [
    File("LICENSE"),
    File("NOTICE"),
]

SDK_INCLUDE: list[File] = [
    File("api/"),
    File("app/"),
    File("cli/"),
    File("vcpkg_triplets/"),
    File("sdk/CMakeLists.txt", "CMakeLists.txt"),
    File("sdk/include.cmake", "include.cmake"),
    File("sdk/packages.cmake", "packages.cmake"),
    File("sdk/subdirs.cmake", "subdirs.cmake"),
    File("sdk/setup.py", "setup.py"),
    File("CMakePresets.json"),
    File("LICENSE"),
    File("NOTICE"),
    File("vcpkg-configuration.json"),
    File("vcpkg.json"),
]
