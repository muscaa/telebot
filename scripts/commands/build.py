import subprocess
import os

import config
from commands import init

def build():
    init.init()

    print("Building...")

    if os.path.exists(f"build/{config.PACKAGE_EXECUTABLE.get_path()}"):
        os.remove(f"build/{config.PACKAGE_EXECUTABLE.get_path()}")

    subprocess.run(["cmake", "--preset", "release"])
    subprocess.run(["cmake", "--build", "--preset", "release"])
