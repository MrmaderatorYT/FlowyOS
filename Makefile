# Визначаємо компілятор і прапори
CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-as
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

CFLAGS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding -march=armv8-a -Wextra -g
ASFLAGS = #
LDFLAGS = -nostdlib -T memmap

# Вихідні файли
SRC_C = notmain.c uart.c ./programs/calc.c strings.c editor.c file_system.c
SRC_ASM = strap.s
OBJ = $(SRC_C:.c=.o) $(SRC_ASM:.s=.o)

# Цільовий файл
TARGET = os.elf
BINARY = os.bin

# Правило за замовчуванням
all: $(TARGET) $(BINARY)

# Правило компіляції C файлів
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Правило асемблерних файлів
%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

# Лінкування об'єктів
$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

# Конвертація в бінарний формат
$(BINARY): $(TARGET)
	$(OBJCOPY) -O binary -R .fuse $< $@

run:
	qemu-system-aarch64 -M virt -cpu cortex-a53 -m 128 -serial null -serial pty -kernel os.bin

# Очищення
clean:
	rm -f $(OBJ) $(TARGET) $(BINARY)

.PHONY: all clean