bits 16

section .data
global disk

disk db 0

section .text
global _start
extern load_kernel ; Defined in ../stage_2/load_kernel.asm

_start:
    mov [disk], dl ; Disk number
    call load_kernel

jmp $