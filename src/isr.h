//
// isr.h -- Interface and structures for high level interrupt service routines.
// Code from JamesM's kernel development tutorials
// @See: interrupt.s
//

#include "common.h"

typedef struct registers
{
    u32int ds;                  // Data segment selector.
    u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha
    u32int int_no, err_code;    // Interrupt number and error code if any
    u32int eip, cs, eflags, useresp, ss; //Pushed by the processor automatically
} registers_t;
