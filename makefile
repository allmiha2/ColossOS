# $@ = target file
# $< = first dependency
# $^ = all dependencies
# | build = ensure build directory exists first

CC = i686-elf-gcc
LD = i686-elf-ld
AS = nasm

CFLAGS = -ffreestanding -fno-pie -fno-pic -Isrc/vga -Isrc/utils

all: run

build:
	mkdir -p build

build/kernel.bin: build/kernel-entry.o build/kernel.o build/vga_text_driver.o build/conversions.o | build
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

build/kernel.o: src/kernel/kernel.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/vga_text_driver.o: src/vga/vga_text_driver.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/conversions.o: src/utils/conversions.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/kernel-entry.o: src/bootloader/kernel-entry.asm | build
	$(AS) $< -f elf32 -o $@

build/boot.bin: src/bootloader/boot.asm | build
	$(AS) $< -f bin -o $@

build/os-image.bin: build/boot.bin build/kernel.bin | build
	cat $^ > $@

run: build/os-image.bin
	qemu-system-i386 -fda $< -boot a

clean:
	$(RM) build/*.bin build/*.o build/*.dis

.PHONY: all run clean