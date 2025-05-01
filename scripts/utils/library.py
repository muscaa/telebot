from utils import platform

class Lib:
    def __init__(self, name: str, platforms: list[str]):
        self.name = name
        self.platforms = platforms

    def __init__(self, name: str):
        self.__init__(name, [platform.WINDOWS, platform.LINUX, platform.MACOS])
