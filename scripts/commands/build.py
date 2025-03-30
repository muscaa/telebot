import subprocess

from commands import init

def build():
    init.init()

    subprocess.run(["cmake", "-S", ".", "-B", "build"])
    subprocess.run(["cmake", "--build", "build"])
