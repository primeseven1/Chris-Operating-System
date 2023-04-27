ASM = nasm -f elf32
CC = i386-elf-gcc -c -m32 -ffreestanding -DRING0 -I ../../include
LD = i386-elf-ld -T kernel.ld -m elf_i386 --oformat binary -nostdlib
LINK_ORDER = -L../../lib/ -lstdlib -ldrivers

ASM_SRC := $(wildcard ./**/*.asm)  $(wildcard ./**/**/*.asm) $(wildcard ./**/**/**/*.asm) $(wildcard ./**/**/**/**/*.asm)
ASM_OBJ := $(patsubst %.asm, %.o, $(ASM_SRC))
C_SRC :=  $(wildcard ./**/*.c) $(wildcard ./**/**/*.c) $(wildcard ./**/**/**/*.c) $(wildcard ./**/**/**/**/*.c)
C_OBJ := $(patsubst %.c, %.o, $(C_SRC))

OUTPUT = ../../bin/kernel.bin

all: $(OUTPUT)

.PHONY: $(OUTPUT)
$(OUTPUT): $(ASM_OBJ) $(C_OBJ)
	$(LD) $(ASM_OBJ) $(C_OBJ) -o $(OUTPUT) $(LINK_ORDER) -O2
# Add a bunch of bytes so that the code can properly jump to the user level code
	dd if=/dev/zero bs=1 count=$$((16384-$$(stat -c "%s" $(OUTPUT)))) >> $(OUTPUT)

%.o: %.asm
	$(ASM) $< -o $@

interrupts/%.o: interrupts/%.c
	$(CC) $< -o $@ -mgeneral-regs-only

%.o: %.c
	$(CC) $< -o $@

clean:
	rm $(ASM_OBJ) $(C_OBJ) $(OUTPUT)