import subprocess

from utils import platform

INITED = False

def init():
    global INITED
    
    if INITED:
        return
    INITED = True

    print(f"Initializing {platform.ARCH}-{platform.SYSTEM}-release...")

    subprocess.run(["vcpkg", "install", "--triplet", f"{platform.ARCH}-{platform.SYSTEM}-release"])
    