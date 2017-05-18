// kheap.h for Organix --> kernel memory heap allocation.
// Based on JamesM's kernel tutorial.
// version 0.1 Alex CREMIEUX

#ifndef KHEAP_H
#define KHEAP_H

#include "common.h"
#include "ordered_array.h"

#define KHEAP_START 0xC0000000
#define KHEAP_INITIAL_SIZE 0x100000
#define HEAP_INDEX_SIZE 0x20000
#define HEAP_MAGIC 0x123890AB
#define HEAP_MIN_SIZE 0x70000

/**Size information for a hole/block.**/
typedef struct
{
    u32int magic;
    u8int is_hole;
    u32int size;
} header_t;

typedef struct
{
    u32int magic;
    header_t *header;
} footer_t;

typedef struct
{
    ordered_array_t index;
    u32int start_address;   // The start of our allocated space.
    u32int end_address;     // The end or out allocated space.
    u32int max_address;     // The maximum address the heap can be expanded to.
    u8int supervisor;       // Should extra pages requested by us be mapped.
    u8int readonly;         // Should extra pages requested by us be mapped.
} heap_t;

/** Creates a new heap. **/
heap_t *create_heap(u32int start, u32int end, u32int max, u8int supervisor,
                    u8int readonly);

/**
    Allocates a contiguous region of memory 'size' in size. If page_align == 1,
    it creates that block starting on a page boundary.
**/
void *alloc(u32int size, u8int page_align, heap_t *heap);

/** Releases a block allocated with 'alloc'. **/
void kfree(void *p);
void free(void *p, heap_t *heap);

u32int kmalloc_int(u32int size, int align, u32int *phys); // kmalloc internal
u32int kmalloc_a(u32int size);
u32int kmalloc_p(u32int size, u32int *phys);
u32int kmalloc_ap(u32int size, u32int *phys);
u32int kmalloc(u32int size);


#endif // KHEAP_H
