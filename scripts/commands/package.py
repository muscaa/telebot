import zipfile

import config
from utils import platform as p
from utils import project

def package():
    print(f"Packaging {project.get_package_zip_name()}...")

    with zipfile.ZipFile(f"build/{project.get_package_zip_name()}", "w", zipfile.ZIP_DEFLATED) as zip:
        if config.PACKAGE_EXECUTABLE.is_valid():
            zip.write(f"build/{config.PACKAGE_EXECUTABLE.get_path()}", config.PACKAGE_EXECUTABLE.get_path_to())
        
        for lib in config.PACKAGE_LIBRARIES:
            if lib.is_valid():
                zip.write(f"build/{lib.get_path()}", lib.get_path_to())

        for file in config.PACKAGE_OTHER:
            if file.is_valid():
                zip.write(file.get_path(), file.get_path_to())
    