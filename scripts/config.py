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

PACKAGE_SDK_INCLUDE: list[str] = [
    "api/",
    "app/",
    "vcpkg_triplets/",
    "CMakePresets.json",
    "vcpkg-configuration.json",
    "vcpkg.json",
]
