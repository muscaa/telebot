import subprocess
import os

import config
from utils import platform

def run():
    print("Running...")

    if os.path.exists(f"build/{config.PACKAGE_EXECUTABLE}{platform.EXT}"):
        subprocess.run([f"build/{config.PACKAGE_EXECUTABLE}{platform.EXT}"])
    else:
        print("No build found.")
