import subprocess

from utils import project

INITED = False

def init():
    global INITED
    
    if INITED:
        return
    INITED = True

    print(f"Initializing {project.get_triplet()}...")

    subprocess.run(["vcpkg", "install", "--triplet", f"{project.get_triplet()}"])
    