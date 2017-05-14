// kheap.h for Organix --> kernel memory heap allocation.
// Based on JamesM's kernel tutorial.
// version 0.1 Alex CREMIEUX

#ifndef KHEAP_H
#define KHEAP_H

#include "common.h"

u32int kmalloc_int(u32int size, int align, u32int *phys); // kmalloc internal
u32int kmalloc_a(u32int size);
u32int kmalloc_p(u32int size, u32int *phys);
u32int kmalloc_ap(u32int size, u32int *phys);
u32int kmalloc(u32int size);

#endif
