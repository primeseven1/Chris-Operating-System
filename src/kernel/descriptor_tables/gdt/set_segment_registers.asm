bits 32

%define KERNEL_CODE_SEGMENT 0x08
%define KERNEL_DATA_SEGMENT 0x10

section .text
global set_kernel_segment_registers

set_kernel_segment_registers:
    jmp KERNEL_CODE_SEGMENT:reload_segments

    reload_segments:
        mov ax, KERNEL_DATA_SEGMENT
        mov ds, ax ; Data segment
        mov ss, ax ; Stack segment
        mov es, ax ; Extra segment
        mov fs, ax ; F segment
        mov gs, ax ; G segment
        
    ret

jmp $