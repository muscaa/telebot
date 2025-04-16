import subprocess

INITED = False

def init():
    global INITED
    
    if INITED:
        return
    INITED = True

    print("Initializing...")

    subprocess.run(["which", "vcpkg"])

    subprocess.run(["vcpkg", "install"])
    