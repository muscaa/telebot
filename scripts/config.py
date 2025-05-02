from utils.package import *
from utils import platform

NAME: str = "telebot"

PACKAGE_EXECUTABLE: Executable = Executable("telebot")
PACKAGE_LIBRARIES: list[Lib] = [
    Lib("SDL3", platforms=[platform.WINDOWS]),
]
PACKAGE_OTHER: list[File] = [
    File("LICENSE"),
    File("NOTICE"),
]
