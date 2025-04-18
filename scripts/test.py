import subprocess
import os

env = os.environ.copy()
print(env)

subprocess.run(["vcpkg", "--version"])
