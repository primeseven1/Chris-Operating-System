#include <libc/string.h>
#include "./gdt.h"

extern uint32_t tss_kernel_stack;
static struct
{
	uint32_t prevTss;
	uint32_t esp0;
	uint32_t ss0;
	// Everything below here is unused.
	uint32_t esp1; // esp and ss 1 and 2 would be used when switching to rings 1 or 2.
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldt;
	uint16_t trap;
	uint16_t iomapBase;
} __attribute__((packed)) tss;

// This can only be called after loading the GDT, doing it before will cause a crash
void loadTSS()
{
    asm volatile("mov %0, %%ax" : : "i"(GDT_ENTRY_TSS));
    asm volatile("ltr %ax");;
}

void GDTSetTSSSegment()
{
	/* prevTss: The previous TSS 
	   esp0: The stack pointer to load when entering back into ring 0 for interrupts
	   ss0: The stack segment to load when entering back into ring 0 for interrupts */

	// At least 1 TSS is required for user level code to run
    memset(&tss, 0, sizeof(tss));
    tss.esp0 = tss_kernel_stack;
    tss.ss0 = GDT_ENTRY_KERNEL_DATA;

    GDTSetEntry(
        GDT_ENTRY_TSS, 
        sizeof(tss), 
        (uint32_t)&tss, 
        GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_DESCRIPTOR_TSS,
        GDT_FLAG_GRANULARITY_1B );
}