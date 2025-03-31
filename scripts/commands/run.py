import subprocess
import os

def run():
    print("Running...")

    if os.path.exists("build/Release/telebot.exe"):
        subprocess.run(["build/Release/telebot.exe"])
    elif os.path.exists("build/telebot"):
        subprocess.run(["build/telebot"])
    else:
        print("No build found.")
