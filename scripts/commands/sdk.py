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
                    if src.startswith(include):
                        zip.write(src, src)
                        added_files[src] = src
                        break

    for src, dst in added_files.items():
        print(f"{src} -> {dst}")
