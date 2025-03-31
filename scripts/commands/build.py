import subprocess
import os

from commands import init

def build():
    init.init()

    print("Building...")

    if os.path.exists("build/Release/telebot.exe"):
        os.remove("build/Release/telebot.exe")
    elif os.path.exists("build/telebot"):
        os.remove("build/telebot")

    subprocess.run(["cmake", "--preset", "conan-default"])
    subprocess.run(["cmake", "--build", "--preset", "conan-release"])
