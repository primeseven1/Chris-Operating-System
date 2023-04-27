bits 16

section .data
extern disk ; Defined in ../stage_1/init.asm

; Defined in ./gdt_info.asm
extern gdt_start
extern code_segment
extern data_segment
extern gdt_descriptor

kernel equ 0x8000

section .text
global load_kernel ; ../stage_1/init.asm needs this

load_kernel:
    mov dh, 0x40 ; Read 64 sectors
    mov bx, kernel ; Where the kernel should be loaded in memory
    mov ah, 0x02 ; Read sectors
    mov al, dh ; Also reading 20 sectors, since you can only use another register to move a value into this one
    mov ch, 0x00 ; Cylinder number
    mov dh, 0x00 ; Head number
    mov cl, 0x02 ; Sector to start from
    mov dl, [disk] ; Disk number
    int 0x13
    call set_video_mode
    jmp load_gdt_start_protected_mode
    
jmp $

set_video_mode:
    mov ah, 0x00 ; Video mode
    mov al, 0x03 ; Setting the video mode to 80x25 16 color text mode
    int 0x10
    ret

load_gdt_start_protected_mode:
    cli ; Disable interrupts before loading the GDT
    lgdt [gdt_descriptor]
    mov eax, cr0 ; Can't flip the protected mode bit directly, so this has to be moved into this register
    or eax, 1 ; Flip the protected mode bit
    mov cr0, eax ; Enable protected mode
    jmp code_segment:jump_to_kernel

jmp $

bits 32
jump_to_kernel:
    mov ax, data_segment ; Setting up segment registers before jumping to the kernel
    mov ds, ax ; Data segment
    mov ss, ax ; Stack segment
    mov es, ax ; Extra segment
    mov fs, ax ; F segment
    mov gs, ax ; G segment

    jmp kernel

jmp $