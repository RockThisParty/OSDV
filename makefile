clear:
	rm -f disk.img bootblock.bin cmain.o pm.o kernel

build:
	dd if=/dev/zero of=disk.img bs=1M count=1
	nasm -fbin bootloader.asm
	dd if=bootloader of=disk.img bs=1 count=512 conv=notrunc
	nasm -felf start.asm -o start.o
	gcc -m32 -fno-pie -nostdlib -nodefaultlibs -nostartfiles -fno-builtin -Wno-int-to-pointer-cast -march=i386 cprint.c -o cp.o
	dd if=kernel of=disk.img bs=512 count=2 seek=1 conv=notrunc
	./start.sh

kernel:
	ld -T linker.ld -o cp.o start.o
