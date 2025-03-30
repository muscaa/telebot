import subprocess

from commands import init

def run():
    init.init()

    subprocess.run(["build/Debug/telebot"])
