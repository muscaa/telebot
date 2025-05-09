import zipfile
import os

import config
from utils import project

def package():
    print(f"Packaging {project.get_package_zip_name()}...")

    build_dir = f"build/{project.get_triplet()}/{project.CONFIGURATION}"
    with zipfile.ZipFile(f"build/{project.get_package_zip_name()}", "w", zipfile.ZIP_DEFLATED) as zip:
        added_files = set()

        if config.PACKAGE_EXECUTABLE.is_valid():
            src = os.path.join(build_dir, config.PACKAGE_EXECUTABLE.get_path())
            dst = config.PACKAGE_EXECUTABLE.get_path_to()
            zip.write(src, dst)
            added_files.add(os.path.normpath(src))

        for lib in config.PACKAGE_LIBRARIES:
            if lib.is_valid():
                src = os.path.join(build_dir, lib.get_path())
                dst = lib.get_path_to()
                zip.write(src, dst)
                added_files.add(os.path.normpath(src))

        for file in config.PACKAGE_OTHER:
            if file.is_valid():
                zip.write(file.get_path(), file.get_path_to())

        for root, _, files in os.walk(build_dir):
            for file in files:
                full_path = os.path.normpath(os.path.join(root, file))
                if full_path not in added_files:
                    rel_path = os.path.relpath(full_path, build_dir)
                    zip.write(full_path, rel_path)
    