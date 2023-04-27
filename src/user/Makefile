ASM = nasm -f elf32
CC = i386-elf-gcc -c -m32 -ffreestanding -DRING3 -I ../../include
LD = i386-elf-ld -T user.ld -m elf_i386 --oformat binary -nostdlib
LINK_ORDER = -L../../lib/ -lstdlib

ASM_SRC := $(wildcard ./**/*.asm)  $(wildcard ./**/**/*.asm) $(wildcard ./**/**/**/*.asm) $(wildcard ./**/**/**/**/*.asm)
ASM_OBJ := $(patsubst %.asm, %.o, $(ASM_SRC))
C_SRC :=  $(wildcard ./**/*.c) $(wildcard ./**/**/*.c) $(wildcard ./**/**/**/*.c) $(wildcard ./**/**/**/**/*.c)
C_OBJ := $(patsubst %.c, %.o, $(C_SRC))

OUTPUT = ../../bin/user.bin

all: $(OUTPUT)

.PHONY: $(OUTPUT)
$(OUTPUT): $(ASM_OBJ) $(C_OBJ)
	$(LD) $(ASM_OBJ) $(C_OBJ) -o $(OUTPUT) $(LINK_ORDER) -O2

%.o: %.asm
	$(ASM) $< -o $@

%.o: %.c
	$(CC) $< -o $@

clean:
	rm $(ASM_OBJ) $(C_OBJ) $(OUTPUT)