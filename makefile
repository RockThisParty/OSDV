clean:
	rm -f bootloader.bin disk.img start.o cmain.o interrupt.o isr.o kernel

build: clean bootloader.bin kernel
	dd if=/dev/zero of=disk.img bs=1M count=1
	dd if=bootloader.bin of=disk.img bs=512 count=1 conv=notrunc
	dd if=kernel of=disk.img bs=512 count=64 seek=1 conv=notrunc
	./start.sh

kernel: cmain.o start.o isr.o common.o
	ld -T linker.ld -o kernel cmain.o start.o isr.o common.o

bootloader.bin: 
	nasm -fbin bootloader.asm -o bootloader.bin

%.o: %.s 
	nasm -felf $^ -o $@

%.o: %.c
	gcc -m32 -fno-pie -nostdlib -nodefaultlibs -nostartfiles -fno-builtin -Wno-int-to-pointer-cast -march=i386 -masm=intel -c -o $@ $^
