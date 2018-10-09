all:
	rm disk.img
	dd if=/dev/zero of=disk.img bs=1M count=1
	nasm -fbin bootloader.asm
	dd if=bootloader of=disk.img bs=1 count=512 conv=notrunc
	dd if=makefile of=disk.img bs=512 count=1 seek=1 conv=notrunc
	dd if=bootloader.asm of=disk.img bs=512 count=1 seek=2 conv=notrunc
