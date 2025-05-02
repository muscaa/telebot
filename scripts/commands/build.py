import subprocess
import os

import config
from commands import init
from utils import platform

def build():
    init.init()

    print("Building...")

    if os.path.exists(f"build/{config.PACKAGE_EXECUTABLE}{platform.EXT}"):
        os.remove(f"build/{config.PACKAGE_EXECUTABLE}{platform.EXT}")

    subprocess.run(["cmake", "--preset", f"{platform.ARCH}-{platform.SYSTEM}-release"])
    subprocess.run(["cmake", "--build", "--preset", f"{platform.ARCH}-{platform.SYSTEM}-release"])
