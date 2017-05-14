//
//
//

#include "paging.h"
#include "kheap.h"
#include "monitor.h"
#include "string.h"

// A bitset of frames - used for free.
u32int *frames;
u32int nframes;

// Defined in kheap.c
extern u32int placement_address;

// kernel directory
static page_directory_t *kernel_directory = 0;
static page_directory_t *current_directory = 0;

// Macros used in the bitset algorithms.
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

// Static function to set a bit in the frames bitset.
static void set_frame(u32int frame_addr)
{
    u32int frame = frame_addr/0x1000;
    u32int idx = INDEX_FROM_BIT(frame);
    u32int off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

// clear a bit in the frames bitset.
static void clear_frame(u32int frame_addr)
{
    u32int frame = frame_addr/0x1000;
    u32int idx = INDEX_FROM_BIT(frame);
    u32int off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
}

// Test if the bit is set.
static u32int test_frame(u32int frame_addr)
{
    u32int frame = frame_addr/0x1000;
    u32int idx = INDEX_FROM_BIT(frame);
    u32int off = OFFSET_FROM_BIT(frame);
    return (frames[idx]  & (0x1 << off));
}

// Find the first frame.
static u32int first_frame()
{
    u32int i, j;
    for(i = 0; i < INDEX_FROM_BIT(nframes); i++)
    {
        // If nothing free --> exit early.
        if(frames[i] != 0xFFFFFFFF)
        {
            for(j = 0; j < 32; j++)
            {
                u32int toTest = 0x1 << j;
                if( !(frames[i] & toTest) )
                {
                    return i * 4 * 8 + j;
                }
            }
        }
    }
}

static void panic(char *str)
{
    monitor_write("Kernel panic: ");
    monitor_write(str);
    while(1);
}

void alloc_frame(page_t *page, int is_kernel, int is_writtable)
{
    if(page->frame != 0)
    {
        return; // Frame was already allocated, return straight away.
    }
    else
    {
        u32int idx = first_frame(); // Idx is now the index of the first free fm.
        if(idx == (u32int)-1)
        {
            // PANIC prints a message to the screen the hits infinite loop.
            panic("No free frames!");
        }
        set_frame(idx * 0x1000);      // This frame is now ours !
        page->present = 1;              // Mark it as present.
        page->rw = (is_writtable) ? 1:0;// Should the page be writtable?
        page->user = (is_kernel) ? 0:1; // Should the page be user-mode?
        page->frame = idx;
    }
}

// Deallocates a frame.
void free_frame(page_t *page)
{
    u32int frame;
    if(!(frame = page->frame))
    {
        return; // The page hasn't an allocated frame!
    }
    else
    {
        clear_frame(frame);
        page->frame = 0x0;
    }
}

void initialise_paging()
{
    u32int mem_end_page = 0x10000000;

    nframes = mem_end_page / 0x1000;
    frames = (u32int*)kmalloc(INDEX_FROM_BIT(nframes));
    memset(frames, 0, INDEX_FROM_BIT(nframes));

    // Makes a page directory.
    kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
    memset(kernel_directory, 0, sizeof(page_directory_t));
    current_directory = kernel_directory;

    // Indetifies map (phys addr = virt addr) from 0x0 to the end of used memory.
    int i = 0;
    while(i < placement_address)
    {
        // Kernel code is readable but not writeable from userspace.
        alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
        i += 0x1000;
    }
    // Before we enable paging, we must register our page fault handler.
    register_interrupt_handler(14, page_fault);

    // Now enables paging!
    switch_page_directory(kernel_directory);
}

void switch_page_directory(page_directory_t *dir)
{
   current_directory = dir;
   asm volatile("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
   u32int cr0;
   asm volatile("mov %%cr0, %0": "=r"(cr0));
   cr0 |= 0x80000000; // Enable paging!
   asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(u32int address, int make, page_directory_t *dir)
{
   // Turn the address into an index.
   address /= 0x1000;
   // Find the page table containing this address.
   u32int table_idx = address / 1024;
   if (dir->tables[table_idx]) // If this table is already assigned
   {
       return &dir->tables[table_idx]->pages[address%1024];
   }
   else if(make)
   {
       u32int tmp;
       dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
       memset(dir->tables[table_idx], 0, 0x1000);
       dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
       return &dir->tables[table_idx]->pages[address%1024];
   }
   else
   {
       return 0;
   }
}

void page_fault(registers_t regs)
{
   // A page fault has occurred.
   // The faulting address is stored in the CR2 register.
   u32int faulting_address;
   asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

   // The error code gives us details of what happened.
   int present   = !(regs.err_code & 0x1); // Page not present
   int rw = regs.err_code & 0x2;           // Write operation?
   int us = regs.err_code & 0x4;           // Processor was in user-mode?
   int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
   int id = regs.err_code & 0x10;          // Caused by an instruction fetch?

   // Output an error message.
   monitor_write("Page fault! ( ");
   if (present) {monitor_write("present ");}
   if (rw) {monitor_write("read-only ");}
   if (us) {monitor_write("user-mode ");}
   if (reserved) {monitor_write("reserved ");}
   monitor_write(") at 0x");
   monitor_write_hex(faulting_address);
   monitor_write("\n");
   panic("Page fault");
}
