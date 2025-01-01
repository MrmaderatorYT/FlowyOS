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
> make

> qemu-system-aarch64 -M virt -cpu cortex-a53 -m 128 -serial mon:stdio -kernel os.bin

або
> qemu-system-aarch64 -M virt -cpu cortex-a53 -m 128 -serial mon:stdio -kernel os.bin -nographic


### Плани розробки
- [ ] команда version
- [ ] файлова система
- [x] програма калькулятора (альтернатива eval)
- [ ] UI



### Для mac:
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

source ~/.zprofile

brew update

brew install qemu make gcc

brew install aarch64-elf-gcc


