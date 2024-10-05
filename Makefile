# Определяем компилятор и флаги
CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-as
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

CFLAGS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding -march=armv8-a
ASFLAGS = #
LDFLAGS = -nostdlib -T memmap

# Исходные файлы
SRC_C = notmain.c uart.c strings.c editor.c file_system.c
SRC_ASM = strap.s
OBJ = $(SRC_C:.c=.o) $(SRC_ASM:.s=.o)

# Целевой файл
TARGET = os.elf
BINARY = os.bin

# Правило по умолчанию
all: $(TARGET) $(BINARY)

# Правило компиляции C файлов
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Правило ассемблерных файлов
%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

# Линковка объектов
$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

# Конвертация в бинарный формат
$(BINARY): $(TARGET)
	$(OBJCOPY) -O binary -R .fuse $< $@

# Очистка
clean:
	rm -f $(OBJ) $(TARGET) $(BINARY)

.PHONY: all clean
