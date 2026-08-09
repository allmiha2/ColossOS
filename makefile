# $@ = target file
# $< = first dependency
# $^ = all dependencies
# | build = ensure build directory exists first

CC = i686-elf-gcc
LD = i686-elf-ld
AS = nasm

CFLAGS = -ffreestanding -fno-pie -fno-pic

all: run

build:
	mkdir -p build

build/kernel.bin: build/kernel-entry.o build/kernel.o | build
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

build/kernel-entry.o: kernel-entry.asm | build
	$(AS) $< -f elf32 -o $@

build/kernel.o: kernel.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/boot.bin: boot.asm | build
	$(AS) $< -f bin -o $@

build/os-image.bin: build/boot.bin build/kernel.bin | build
	cat $^ > $@

run: build/os-image.bin
	qemu-system-i386 -fda $< -boot a

clean:
	$(RM) build/*.bin build/*.o build/*.dis

.PHONY: all run clean