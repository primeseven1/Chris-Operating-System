section .data

; Needed by ./load_kernel.asm
global gdt_start
global code_segment
global data_segment
global gdt_descriptor

gdt_start:
    gdt_null:
        dd 0x0000
        dd 0x0000

    gdt_code:
        dw 0xffff
        dw 0x0000
        db 0x0000
        db 0b10011010
        db 0b11001111
        db 0x0000

    gdt_data:
        dw 0xffff
        dw 0x0000
        db 0x0000
        db 0b10010010
        db 0b11001111
        db 0x0000
gdt_end:

code_segment: equ gdt_code - gdt_start
data_segment: equ gdt_data - gdt_start

gdt_descriptor: 
    dw gdt_end - gdt_start - 1 
    dd gdt_start