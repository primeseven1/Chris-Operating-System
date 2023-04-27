import os
import sys
import subprocess

dirs = ["../lib_src", "../src/boot", "../kernel", "../user"]

def make(file_path: str):
    os.chdir(file_path)
    result = subprocess.run(['make'], capture_output=True, text=True)

    if result.returncode == 0:
        print(result.stdout)
        print("\033[32mMake success!\033[0m")

    else:
        print(f"\033[31m{result.stderr}")
        sys.exit(1)

if __name__ == "__main__":
    for file_path in dirs:
        make(file_path)