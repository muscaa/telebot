import subprocess

INITED = False

def init():
    global INITED
    
    if INITED:
        return
    INITED = True

    print(f"Initializing...")

    subprocess.run(["vcpkg", "install"])
    