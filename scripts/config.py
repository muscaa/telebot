from utils.library import Lib
from utils import platform

NAME: str = "telebot"

PACKAGE_EXECUTABLE: str = "telebot"
PACKAGE_LIBRARIES: list[Lib] = [
    Lib("SDL3", [platform.WINDOWS]),
]
PACKAGE_OTHER: dict[str, str] = {
    "LICENSE": "LICENSE",
    "NOTICE": "NOTICE",
}
