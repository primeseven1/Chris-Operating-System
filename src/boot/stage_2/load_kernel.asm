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
global load_kernel ; for ../stage_1/init.asm

load_kernel:
    mov dh, 0x40 ; Read 64 sectors
    mov bx, kernel ; Memory location
    mov ah, 0x02 ; Read sectors
    mov al, dh ; 64 sectors
    mov ch, 0x00 ; Cylinder number
    mov dh, 0x00 ; Head number
    mov cl, 0x02 ; Sector to start from
    mov dl, [disk] ; Disk number
    int 0x13

set_video_mode:
    mov ah, 0x00 ; Video mode
    mov al, 0x03 ; 80x25 16 color text mode
    int 0x10

start_protected_mode:
    cli ; Disable interrupts before loading the GDT
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1 ; Flip the protected mode bit
    mov cr0, eax
    jmp code_segment:jump_to_kernel

bits 32
jump_to_kernel:
    mov ax, data_segment
    mov ds, ax ; Data segment
    mov ss, ax ; Stack segment
    mov es, ax ; Extra segment
    mov fs, ax ; F segment
    mov gs, ax ; G segment

    jmp kernel

jmp $