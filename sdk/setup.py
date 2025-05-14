import os
import shutil

def already_exists(root: str, to_move: list[str]) -> bool:
    for item in to_move:
        src = os.path.join(root, item)
        dst = os.path.join(os.getcwd(), item)

        if os.path.isdir(src):
            if os.path.exists(dst):
                return True
        elif os.path.isfile(src):
            if os.path.exists(dst):
                return True
            
    return False

def move_files(root: str):
    to_move = ["vcpkg_triplets/", "CMakePresets.json", "vcpkg-configuration.json", "vcpkg.json"]
    exists = already_exists(root, to_move)

    if exists:
        print("Necessary files already exist, skipping...")
        for item in to_move:
            src = os.path.join(root, item)

            if os.path.isdir(src):
                shutil.rmtree(src)
            elif os.path.isfile(src):
                os.remove(src)
    else:
        print("Moving necessary files...")
        for item in to_move:
            src = os.path.join(root, item)
            dst = os.path.join(os.getcwd(), item)

            if os.path.isdir(src):
                shutil.move(src, dst)
            elif os.path.isfile(src):
                os.makedirs(os.path.dirname(dst), exist_ok=True)
                shutil.move(src, dst)

def main():
    root = os.path.dirname(__file__)

    move_files(root)

    print("Setup complete!")
