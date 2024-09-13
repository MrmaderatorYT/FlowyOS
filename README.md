Вам потрібно заватнажити wsl для windows.
В PowerShell прописати команду від імені адміністратора:
wsl --install

Обираєте Ubuntu. Згодом встановлюєте імена користувача та пароль.
Використовуєте команди:
sudo apt update
sudo apt upgrade

І завантажуємо необхідні компоненти (емулятор, компілятор ассемблерного коду та С/С++)
sudo apt install build-essential gcc-arm-none-eabi qemu-system-arm

І запукаємо:
arm-none-eabi-as --warn --fatal-warnings -march=armv5t strap.s -o strap.o
arm-none-eabi-gcc -c -Wall -O2 -nostdlib -nostartfiles -ffreestanding -march=armv5t notmain.c -o notmain.o
arm-none-eabi-ld strap.o notmain.o -T memmap -o notmain.elf
arm-none-eabi-objcopy notmain.elf -O binary notmain.bin

qemu-system-arm -M versatilepb -m 128M -nographic -kernel os.bin

Отримуємо Hello, from ASM!
