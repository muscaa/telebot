import zipfile
import os

import config

def sdk():
    print(f"Generating SDK...")

    added_files = {}
    with zipfile.ZipFile(f"build/sdk.zip", "w", zipfile.ZIP_DEFLATED) as zip:
        for root, _, files in os.walk("."):
            for file in files:
                src = os.path.normpath(os.path.join(root, file))

                for include in config.PACKAGE_SDK_INCLUDE:
                    if src.startswith(include):
                        zip.write(src, src)
                        added_files[src] = src
                        break

    for src, dst in added_files.items():
        print(f"{src} -> {dst}")
