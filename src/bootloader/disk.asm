disk_load:
    ; save state of CPU, push all registers to stack
    pusha
    ; we are pushing the number of sectors to read (which is stored in the 
    ; high part of the the dx register) to the stack because we need to set 
    ; dh to the head number before sending the BIOS interrupt signal and we want
    ; to compare the expected number of sectors read to the actual one reported by
    ; BIOS to detect errors when we are done.

    ; only push dx as a local variable to use later
    push dx

    mov ah, 0x02 ; read mode
    mov al, dh ; read dh number of sectors
    mov cl, 0x02 ; start from sector 2 (sector 1 is the boot sector - bootloader)
    mov ch, 0x00 ; cylinder 0
    mov dh, 0x00 ; head 0

    ; dl is the drive number ( was set as input of disk_load)
    ; bx is pointer to buffer: destination where to store the read data into 

    int 0x13 ; BIOS interrupt to execute read
    jc disk_error ; if carry bit true, jump to routine to handle error

    pop dx ; get back the stored number of sectors intended to read
    cmp al, dh ; after read execution, BIOS sets al to the number of sectors actually read
    jne sectors_error

    popa ; restore CPU state from before entering this routine
    ret
    
disk_error:
    jmp disk_loop

sectors_error:
    jmp disk_loop

disk_loop:
    jmp $

