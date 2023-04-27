ASM = nasm -f elf32
LD = i386-elf-ld -T bootloader.ld -m elf_i386 --oformat binary -nostdlib

SRC := $(wildcard ./**/*.asm)
OBJ := $(patsubst %.asm, %.o, $(SRC))

OUTPUT = ../../bin/bootloader.bin

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(LD) $(OBJ) -o $(OUTPUT)

#	Padding the bootloader with zeros, and adding the boot signature at the end
	dd if=/dev/zero bs=1 count=$$((510-$$(stat -c "%s" $(OUTPUT)))) >> $(OUTPUT)
	dd if=/dev/zero bs=1 count=1 | tr "\000" "\125" >> $(OUTPUT)
	dd if=/dev/zero bs=1 count=1 | tr "\000" "\252" >> $(OUTPUT)

%.o: %.asm
	$(ASM) $< -o $@

clean:
	rm $(OBJ) $(OUTPUT)