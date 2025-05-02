import subprocess
import os

import config

def run():
    print("Running...")

    if os.path.exists(f"build/{config.PACKAGE_EXECUTABLE.get_path()}"):
        subprocess.run([f"build/{config.PACKAGE_EXECUTABLE.get_path()}"])
    else:
        print("No build found.")
