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
    File("vcpkg_triplets/"),
    File("CMakePresets.json"),
    File("LICENSE"),
    File("NOTICE"),
    File("vcpkg-configuration.json"),
    File("vcpkg.json"),
]
