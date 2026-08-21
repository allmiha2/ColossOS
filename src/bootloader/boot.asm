[bits 16]
[org 0x7c00]

; where to load the kernel to
KERNEL_OFFSET equ 0x1000

; BIOS stores the selected boot drive in the dl register, 
; store for later use at end of bootloader program
mov [BOOT_DRIVE], dl

; move the stack and base pointers far enough away from bootloader section
mov bp, 0x9000
mov sp, bp

call load_kernel
call switch_to_32bit

; loop here if fall through above to not execute unkown memory
jmp $

%include "src/bootloader/disk.asm"
%include "src/bootloader/gdt.asm"
%include "src/bootloader/switch-to-32bit.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET ; bx destination
    mov dh, 2 ; dh num of sectors
    mov dl, [BOOT_DRIVE] ; dl - disk
    call disk_load
    ret

[bits 32]
BEGIN_32BIT:
    call KERNEL_OFFSET ; give control to kernel
    jmp $ ; loop if fall through

;boot drive variable, BOOT_DRIVE is an alias for the memory location of this line
BOOT_DRIVE db 0

; padding
times 510 - ($-$$) db 0

; magic number at end
dw 0xaa55
