CC = i386-elf-gcc -c -m32 -ffreestanding -I../include
AR = i386-elf-ar rcs

LIBC_SRC := $(wildcard ./libc/*.c)
LIBC_OBJ := $(patsubst %.c, %.o, $(LIBC_SRC))
DRIVERS_SRC := $(wildcard ./drivers/**/*.c)
DRIVERS_OBJ := $(patsubst %.c, %.o, $(DRIVERS_SRC))

LIBC_OUT = ../lib/libstdlib.a
DRIVERS_OUT = ../lib/libdrivers.a

all: $(LIBC_OUT) $(DRIVERS_OUT)

$(LIBC_OUT): $(LIBC_OBJ)
	$(AR) $(LIBC_OUT) $(LIBC_OBJ)

$(DRIVERS_OUT): $(DRIVERS_OBJ)
	$(AR) $(DRIVERS_OUT) $(DRIVERS_OBJ)

./libc/%.o: ./libc/%.c
	$(CC) -DRING3 $< -o $@

./drivers/%.o: ./drivers/%.c
	$(CC) -DRING0 $< -o $@

clean:
	rm $(LIBC_OBJ) $(DRIVERS_OBJ) $(LIBC_OUT) $(DRIVERS_OUT)