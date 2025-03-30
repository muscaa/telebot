import subprocess
import os
import shutil

from commands import init

def build():
    init.init()

    print("Building...")

    if os.path.exists("build/Release/"):
        shutil.rmtree("build/Release/")

    subprocess.run(["cmake", "-S", ".", "-B", "build"])
    subprocess.run(["cmake", "--build", "build", "--config", "Release"])
