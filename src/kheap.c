// kheap.c

#include "kheap.h"
#include "common.h"

// end is defined int he linked script.
extern u32int end;
u32int placement_address = (u32int)&end;

u32int kmalloc_int(u32int size, int align, u32int *phys)
{
    // if the adress is not already page-aligned: align it.
    if(align == 1 && (placement_address & 0xFFFFF000))
    {
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }

    if(phys)
    {
        *phys = placement_address;
    }

    u32int tmp = placement_address;
    placement_address += size;
    return tmp;
}

// Vanilla.
u32int kmalloc(u32int size)
{
    return kmalloc_int(size, 0, 0);
}

// Page aligned.
u32int kmalloc_a(u32int size)
{
    return kmalloc_int(size, 1, 0);
}

// returns physical address.
u32int kmalloc_p(u32int size, u32int *phys)
{
    return kmalloc_int(size, 0, phys);
}

// page aligned and returns physical address.
u32int kmalloc_ap(u32int size, u32int *phys)
{
    return kmalloc_int(size, 1, phys);
}
