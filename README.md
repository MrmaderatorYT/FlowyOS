Вам потрібно заватнажити wsl для windows.
В PowerShell прописати команду від імені адміністратора:
> wsl --install

Обираєте Ubuntu. Згодом встановлюєте імена користувача та пароль.
Використовуєте команди:
> sudo apt update
> sudo apt upgrade

І завантажуємо необхідні компоненти (емулятор, компілятор ассемблерного коду та С/С++)
sudo apt install build-essential aarch64-linux-gnu qemu-system-arm

І запукаємо:
> aarch64-linux-gnu-as --warn --fatal-warnings -march=armv8-a strap.s -o strap.o

> aarch64-linux-gnu-gcc -c -Wall -O2 -nostdlib -nostartfiles -ffreestanding -march=armv8-a notmain.c -o notmain.o

> aarch64-linux-gnu-ld strap.o notmain.o -T memmap -o notmain.elf

> aarch64-linux-gnu-objcopy notmain.elf -O binary os.bin

> qemu-system-aarch64 -M virt -cpu cortex-a53 -m 128 -serial mon:stdio -kernel os.bin


Отримуємо можливість введення та виведення даних з клавіатури
