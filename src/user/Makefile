CC = i386-elf-gcc -c -m32 -ffreestanding -DRING3 -I ../../include
LD = i386-elf-ld -T user.ld -m elf_i386 --oformat binary -nostdlib
LINK_ORDER = -L../../lib/ -lstdlib

C_SRC :=  $(wildcard ./**/*.c) $(wildcard ./**/**/*.c)
C_OBJ := $(patsubst %.c, %.o, $(C_SRC))

OUTPUT = ../../bin/user.bin

all: $(OUTPUT)

.PHONY: $(OUTPUT)
$(OUTPUT): $(C_OBJ)
	$(LD) $(C_OBJ) -o $(OUTPUT) $(LINK_ORDER) -O2

%.o: %.c
	$(CC) $< -o $@

clean:
	rm $(C_OBJ) $(OUTPUT)