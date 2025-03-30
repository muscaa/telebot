import subprocess
import os

from commands import init

def run():
    init.init()

    print("Running...")

    if not os.path.exists("build/Release/telebot") and not os.path.exists("build/Release/telebot.exe"):
        print("No build found.")
        return

    subprocess.run(["build/Release/telebot"])
