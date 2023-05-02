bits 32

section .data
global tss_kernel_stack ; Needed by ../kernel_modules/cpu/gdt/tss.c

tss_kernel_stack dd kernel_stack_top
user_code equ 0x8000 + 0x4000

section .bss
stack_bottom:
    resb 16384
stack_top:

kernel_stack_bottom:
    resb 16384
kernel_stack_top:

user_stack_bottom:
    resb 32768
user_stack_top:

section .text
global start_kernel ; Needed by linker
extern kmain ; Defined in main.c

start_kernel:
    mov esp, stack_top
    mov ebp, esp

    call kmain

start_user_mode:
	mov ax, (4 * 8) | 3 ; ring 3 data with bottom 2 bits set for ring 3
	mov ds, ax ; Data segment
	mov es, ax ; Extra segment
	mov fs, ax ; F segment
	mov gs, ax ; G segment

	mov esp, user_stack_top
	mov ebp, esp

	; set up the stack frame iret expects
	mov eax, esp
	push (4 * 8) | 3 ; data selector
	push eax ; esp
	pushf ; eflags
	push (3 * 8) | 3 ; code selector with ring 3
	push user_code ; returning to user code
	iret

jmp $
