CC = aarch64-elf-gcc
AS = aarch64-elf-as
LD = aarch64-elf-ld
OBJCOPY = aarch64-elf-objcopy

CFLAGS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding -march=armv8-a -Wextra -g
ASFLAGS = #
LDFLAGS = -nostdlib -T memmap

SRC_C = kernel.c uart.c programs/calc.c programs/log.c strings.c editor.c file_system.c
SRC_ASM = start.asm
OBJ = $(SRC_C:.c=.o) $(SRC_ASM:.asm=.o)

TARGET = os.elf
BINARY = os.bin

all: $(TARGET) $(BINARY)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(BINARY): $(TARGET)
	$(OBJCOPY) -O binary -R .fuse $< $@

run:
	qemu-system-aarch64 -M virt -cpu cortex-a53 -m 128 -nographic -kernel os.bin
clean:
	rm -f $(OBJ) $(TARGET) $(BINARY)

.PHONY: all clean run
