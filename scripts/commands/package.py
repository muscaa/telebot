import zipfile
import os

import config
from utils import project

def package():
    print(f"Packaging {project.get_package_zip_name()}...")

    zip_file = f"build/{project.get_sdk_zip_name()}"
    os.makedirs(os.path.dirname(zip_file), exist_ok=True)

    added_files = {}
    build_dir = f"build/{project.get_triplet()}/{project.CONFIGURATION}"
    with zipfile.ZipFile(zip_file, "w", zipfile.ZIP_DEFLATED) as zip:
        if config.PACKAGE_EXECUTABLE.is_valid():
            src = os.path.join(build_dir, config.PACKAGE_EXECUTABLE.get_path())
            dst = config.PACKAGE_EXECUTABLE.get_path_to()
            zip.write(src, dst)
            added_files[src] = dst

        for lib in config.PACKAGE_LIBRARIES:
            if lib.is_valid():
                src = os.path.join(build_dir, lib.get_path())
                dst = lib.get_path_to()
                zip.write(src, dst)
                added_files[src] = dst

        for file in config.PACKAGE_OTHER:
            if file.is_valid():
                src = file.get_path()
                dst = file.get_path_to()
                zip.write(src, dst)
                added_files[src] = dst

        for root, _, files in os.walk(build_dir):
            for file in files:
                src = os.path.join(root, file)
                if src not in added_files:
                    dst = os.path.relpath(src, build_dir)
                    zip.write(src, dst)
                    added_files[src] = dst

    for src, dst in added_files.items():
        print(f"{src} -> {dst}")
