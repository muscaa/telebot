import subprocess
import os

env = os.environ.copy()
print(env)

subprocess.run(["which", "vcpkg"])
subprocess.run(["vcpkg", "--version"])
