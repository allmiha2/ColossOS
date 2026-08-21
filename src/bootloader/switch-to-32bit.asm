[bits 16]
switch_to_32bit:
    cli ; disable interrupts
    lgdt [gdt_descriptor] ; load gdt descriptor

    mov eax, cr0
    or eax, 0x1 ; enable protected mode (CR0 contains many control bits, we ony one to set the protected-enabled one)
    mov cr0, eax

    ; p until this mode protected is enabled but CS is still real mode one, need to put it to new
    ; protected mode code segment selector

    jmp CODE_SEG:init_32bit ; far jump: not only jump there, but also update CS with the new code segment selector

[bits 32]
init_32bit:
    mov ax, DATA_SEG ; update segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax ; all these are data related registers (ss is for stack accesses, rest is data or extra data)

    mov ebp, 0x90000
    mov esp, ebp ; set up stack

    call BEGIN_32BIT