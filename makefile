# # $@ = target file
# # $< = first dependency
# # $^ = all dependencies

# # First rule is the one executed when no parameters are fed to the Makefile
# all: run

# build/kernel.bin: build/kernel-entry.o build/kernel.o
# 	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

# build/kernel-entry.o: kernel-entry.asm
# 	nasm $< -f elf -o $@

# build/kernel.o: kernel.c
# 	gcc -m32 -ffreestanding -fno-pie -fno-pic -c $< -o $@

# build/boot.bin: boot.asm
# 	nasm $< -f bin -o $@

# build/os-image.bin: build/boot.bin build/kernel.bin
# 	cat $^ > $@

# run: build/os-image.bin
# 	qemu-system-i386 -fda $< -boot a

# clean:
# 	$(RM) *.bin *.o *.dis

# clean:
# 	$(RM) build/*.bin build/*.o build/*.dis

# $@ = target file
# $< = first dependency
# $^ = all dependencies

# | build: make sure the build folder exists before building this file

all: run

build:
	mkdir -p build

build/kernel.bin: build/kernel-entry.o build/kernel.o | build
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

build/kernel-entry.o: kernel-entry.asm | build
	nasm $< -f elf -o $@

build/kernel.o: kernel.c | build
	gcc -m32 -ffreestanding -fno-pie -fno-pic -c $< -o $@

build/boot.bin: boot.asm | build
	nasm $< -f bin -o $@

build/os-image.bin: build/boot.bin build/kernel.bin | build
	cat $^ > $@

run: build/os-image.bin
	qemu-system-i386 -fda $< -boot a

clean:
	$(RM) build/*.bin build/*.o build/*.dis