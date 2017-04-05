;
; boot.s -- Kernel start location. Also defines multiboot header.
; Based on Bran's kernel development tutorial file start.asm
;

MBOOT_PAGE_ALIGN   equ 1<<0 ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO     equ 1<<1 ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC equ 0x1BADB002 ; Multiboot Magic Value ???
MBOOT_HEADER_FLAGS equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM     equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]
