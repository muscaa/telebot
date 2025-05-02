import subprocess
import os

import config
from commands import init
from utils import project

def build():
    init.init()

    print("Building...")

    if os.path.exists(f"build/{project.get_triplet()}/{config.PACKAGE_EXECUTABLE.get_path()}"):
        os.remove(f"build/{project.get_triplet()}/{config.PACKAGE_EXECUTABLE.get_path()}")

    subprocess.run(["cmake", "--preset", f"{project.get_triplet()}"])
    subprocess.run(["cmake", "--build", "--preset", f"{project.get_triplet()}"])
