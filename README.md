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
> aarch64-linux-gnu-as -march=armv8-a strap.s -o strap.o

> aarch64-linux-gnu-gcc -c -Wall -O2 -nostdlib -nostartfiles -ffreestanding -march=armv8-a notmain.c -o notmain.o

> aarch64-linux-gnu-gcc -nostdlib -T memmap notmain.o strap.o -o os.elf

> aarch64-linux-gnu-objcopy -O binary -R .fuse os.elf os.bin

> qemu-system-aarch64 -M virt -cpu cortex-a53 -m 128 -serial mon:stdio -kernel os.bin


### Плани розробки
- [ ] команда version
- [ ] файлова система
