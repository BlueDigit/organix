//
// isr.c -- Handle level interrupt service routines and interrupt request handlers.
// Code from JamesM's kernel developement tutorials
//

#include "common.h"
#include "isr.h"
#include "monitor.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    monitor_write("recieved interrupt: ");
    monitor_write_dec(regs.int_no);
    monitor_put('\n');
}
