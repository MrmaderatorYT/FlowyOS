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


### Плани розробки
- [ ] команда version
- [ ] файлова система
