import zipfile
import os

import config
from utils import project

def sdk():
    print(f"Packaging {project.get_sdk_zip_name()}...")

    added_files = {}
    with zipfile.ZipFile(f"build/{project.get_sdk_zip_name()}", "w", zipfile.ZIP_DEFLATED) as zip:
        for root, _, files in os.walk("."):
            for file in files:
                src = os.path.normpath(os.path.join(root, file))

                for include in config.SDK_INCLUDE:
                    if src.startswith(os.path.normpath(include.get_path())):
                        if include.is_valid():
                            dst = os.path.normpath(os.path.join(include.get_path_to(), os.path.relpath(src, include.get_path())))
                            zip.write(src, dst)
                            added_files[src] = dst
                        break

    for src, dst in added_files.items():
        print(f"{src} -> {dst}")
