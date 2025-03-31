import subprocess
import os

def run():
    print("Running...")

    if os.path.exists("build/telebot.exe"):
        subprocess.run(["build/telebot.exe"])
    elif os.path.exists("build/telebot"):
        subprocess.run(["build/telebot"])
    else:
        print("No build found.")
