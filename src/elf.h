//
// elf.h -- Defines routines for dealing with Executable and Linking Format files.
//          Written for JamesM's kernel developement tutorials.
//

#ifndef ELF_H
#define ELF_H

#include "common.h"
#include "multiboot.h"

#define ELF32_ST_TYPE(i) ((i)&0xf)

typedef struct
{
  u32int name;
  u32int type;
  u32int flags;
  u32int addr;
  u32int offset;
  u32int size;
  u32int link;
  u32int info;
  u32int addralign;
  u32int entsize;
} __attribute__((packed)) elf_section_header_t;

typedef struct
{
  u32int name;
  u32int value;
  u32int size;
  u8int  info;
  u8int  other;
  u16int shndx;
} __attribute__((packed)) elf_symbol_t;

typedef struct
{
  elf_symbol_t *symtab;
  u32int      symtabsz;
  const char   *strtab;
  u32int      strtabsz;
} elf_t;

// Takes a multiboot structure and returns an elf structure containing the symbol information.
elf_t elf_from_multiboot (multiboot_header_t *mb);

// Looks up a symbol by address.
char *elf_lookup_symbol (u32int addr, elf_t *elf);

#endif // ELF_H
