from utils import platform

class Lib:
    def __init__(self, name: str, platforms: list[str] = [platform.WINDOWS, platform.LINUX, platform.MACOS]):
        self.name = name
        self.platforms = platforms
