import sys

def main():
    for arg in sys.argv[1:]:
        # im bored, hackish method
        exec(f"from commands.{arg} import {arg}")
        exec(f"{arg}()")

if __name__ == "__main__":
    main()
