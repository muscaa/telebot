import zipfile

import config
from utils import platform

def package():
    print("Packaging...")

    with zipfile.ZipFile(f"build/{config.NAME}-{platform.SYSTEM}-{platform.ARCH}.zip", "w", zipfile.ZIP_DEFLATED) as zip:
        zip.write(f"build/{config.PACKAGE_EXECUTABLE}{platform.EXT}", f"{config.PACKAGE_EXECUTABLE}{platform.EXT}")
        
        for lib in config.PACKAGE_LIBRARIES:
            zip.write(f"build/{lib}{platform.LIB_EXT}", f"{lib}{platform.LIB_EXT}")

        for file, name in config.PACKAGE_OTHER.items():
            zip.write(file, name)
    