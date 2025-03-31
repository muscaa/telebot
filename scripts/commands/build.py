import subprocess
import os

from commands import init

def build():
    init.init()

    print("Building...")

    if os.path.exists("build/telebot.exe"):
        os.remove("build/telebot.exe")
    elif os.path.exists("build/telebot"):
        os.remove("build/telebot")

    subprocess.run(["cmake", "--preset", "default"])
    subprocess.run(["cmake", "--build", "--preset", "release"])
