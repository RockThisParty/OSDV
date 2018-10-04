all:
	rm disk.img
	dd if=/dev/zero of=disk.img bs=1M count=1
	nasm -fbin bootloader.asm
	dd if=bootloader of=disk.img bs=1 count=512 conv=notrunc

	

