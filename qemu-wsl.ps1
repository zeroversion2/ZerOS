#!/mnt/c/Windows/System32/WindowsPowerShell/v1.0/powershell.exe
cp ZerOS.iso ~
cd ~
qemu-system-x86_64.exe -accel whpx -display sdl -cdrom ./ZerOS.iso -serial stdio
