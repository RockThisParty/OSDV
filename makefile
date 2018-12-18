clean:
	rm -f bootloader.bin disk.img start.o cp.o kernel

build: clean bootloader.bin kernel
	dd if=/dev/zero of=disk.img bs=1M count=1
	dd if=bootloader.bin of=disk.img bs=512 count=1 conv=notrunc
	dd if=kernel of=disk.img bs=512 count=2 seek=1 conv=notrunc
	./start.sh

kernel: start.o cp.o
	ld -T linker.ld -o kernel cp.o start.o

bootloader.bin: 
	nasm -fbin bootloader.asm -o bootloader.bin

start.o: 
	nasm -felf start.asm -o start.o

cp.o:
	gcc -m32 -fno-pie -nostdlib -nodefaultlibs -nostartfiles -fno-builtin -Wno-int-to-pointer-cast -march=i386 -c -o cp.o cprint.c
