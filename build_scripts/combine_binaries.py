import sys

def combine():
    try:
        with open("../bin/bootloader.bin", "rb") as bootloader:
            bootloader_data = bootloader.read()
            
        with open("../bin/kernel.bin", "rb") as kernel:
            kernel_data = kernel.read()

        with open("../bin/user.bin", "rb") as user:
            user_data = user.read()

        with open("../bin/OS.bin", "wb") as OS:
            OS.write(bootloader_data + kernel_data + user_data)

    except:
        sys.exit(1)

if __name__ == "__main__":
    combine()